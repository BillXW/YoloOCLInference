//
// Created by ubuntu on 5/22/18.
//

#define BOOST_TEST_MODULE image2Array7x7Tests

#include <boost/test/unit_test.hpp>
#include<iostream>
#include "OCLManager.h"
#include <limits.h>
#include <unistd.h>
#include <YoloOCLDNN.h>
#include "buffer.h"
#include "YoloOCLDNN.h"
#include <cstdlib>

using  namespace std;

#define DEL_(name) do { if( NULL != (name) ) { delete (name); (name) = NULL; } } while(0)
#define rand01 rand() / double(RAND_MAX) ;


//YOLONeuralNet	*m_YOLODeepNNObj;

/*BOOST_AUTO_TEST_CASE(FailTest) {
    BOOST_CHECK_EQUAL(1,1);
}*/

int zeroCount(float *array, int len){
    int count = 0;
    for (int i =0; i <len; i++) {
        if (array[i] == 0) {
            count++;
        }
    }
    return count;
}

template<typename T>

int initArray(T* array, int rowNum, int colNum, T value ,bool is_rand = false) {
    int count = 0;
    for(int i=0; i<rowNum; i++) {
        for(int j =0; j<colNum; j++) {
            count ++;
            if(!is_rand) {
                array[i * colNum + j] = value;
            } else {
                array[i*colNum+j] = rand01;
            }
        }
    }
    return count;
}


BOOST_AUTO_TEST_CASE(kernel7x7) {
    int in_ch = 3;
    int in_w = 416;
    int in_h = 416;
    int stride = 1;
    int padding = 1;
    int kernel_size = 7;

    int out_ch = 16;
    int out_w = ((in_w + 2*padding - kernel_size) / stride) + 1;
    int out_h = ((in_h + 2*padding - kernel_size) / stride)+ 1;

    int m = out_ch; // 16
    int n =  out_w * out_h; // (412 * 412)
    int k = in_ch * kernel_size * kernel_size ; // 3 * 7 * 7


    float *data_img = new float[in_ch * in_w * in_h]; // 3 * 416 * 416
    float *data_img9x = new float[in_ch * kernel_size * kernel_size * out_w * out_h]; // (3 * 7 * 7) * (412 * 412)
    float *data_out = new float[out_ch * out_w * out_h]; // 16 * 412 * 412
    float * kernel_weights = new float[out_ch * in_ch * kernel_size * kernel_size]; // 16 * 3 * 7 * 7


    initArray<float> (data_img, in_ch, in_w*in_h, 1.0f) ;
    initArray<float> (data_img9x, in_ch * kernel_size * kernel_size, out_w * out_h, 1.0f);
    initArray<float> (data_out, out_ch, out_w * out_h, 0.0f);
    initArray<float> (kernel_weights, out_ch, in_ch * kernel_size* kernel_size, 1.0);


    OCLManager *manager = new OCLManager();
    manager->Initialize();

    OCLBuffer *bufImg = manager->InitializeFloatArray(data_img, in_ch * in_w * in_h); // 3*416*416
    PrintOCLBuffer(bufImg, manager, "bufImg_before7x7.bin",  in_ch * in_w * in_h);

    OCLBuffer *bufImg9x = manager->InitializeFloatArray(data_img9x, in_ch * kernel_size * kernel_size * out_w * out_h);
    PrintOCLBuffer(bufImg9x, manager, "bufImg9x_before7x7.bin",  in_ch * kernel_size * kernel_size * out_w * out_h);


    OCLBuffer *buf_out = manager->InitializeFloatArray(data_out, out_ch * out_w * out_h);
    PrintOCLBuffer(buf_out, manager, "buf_out_before7x7.bin", out_ch * out_w * out_h);

    OCLBuffer *weights_gpu = manager->InitializeFloatArray(kernel_weights, out_ch * in_ch * kernel_size * kernel_size);
    PrintOCLBuffer(weights_gpu, manager, "weights_gpu7x7.bin", out_ch * in_ch * kernel_size * kernel_size);

    //manager->ConvertImageToColumnArray(bufImg, 3, 416, 416, 3, 1, 1, bufImg9x);
    //PrintOCLBuffer(bufImg9x, manager, "bufImg9x_after.bin",  27*416*416);

    manager->ConvertImageToColumnArray(bufImg, in_ch, in_w, in_h, kernel_size, stride, padding, bufImg9x);
    PrintOCLBuffer(bufImg9x, manager, "bufImg9x_after.bin",  in_ch * kernel_size * kernel_size * out_w * out_h);

    manager->ComputeGEMM(false, false, m, n, k, 1.0f, weights_gpu, 0, k,
                         bufImg9x, 0, n , 1.0f, buf_out, 0, n);
    PrintOCLBuffer(buf_out, manager, "buf_out_after7x7.bin",  out_ch * out_w * out_h);


    DEL_(data_img);
    DEL_(data_img9x);
    DEL_(data_out);
    DEL_(kernel_weights);
    DEL_(bufImg);
    DEL_(bufImg9x);
    DEL_(buf_out);
    DEL_(weights_gpu);
    DEL_(manager);

}


BOOST_AUTO_TEST_CASE(kernel3x3) {
    StructImage	*m_ResizedImage = new StructImage();

    m_ResizedImage->m_C = 3;
    m_ResizedImage->m_H = 416;
    m_ResizedImage->m_W = 416;
    srand(1234);

    int flatNumIn = m_ResizedImage->m_C *  m_ResizedImage->m_H *  m_ResizedImage->m_W;
    int flatNumOut= m_ResizedImage->m_C *  m_ResizedImage->m_H *  m_ResizedImage->m_W;

    int data_img_len = 3*416*416;

    float *data_img = new float [3*416*416];

    float *data_in = new float [27*416*416];  // the input to GEMM will be 9 times bigger than data_img

    float *data_out= new float [16*416*416];
    float *kernel_weights = new float[16*27];



    int data_img_count = 0;
    for(int i =0; i<3; i++) {
        for(int j=0; j < 173056; j++){
            //data_img[i*3+j] = (i+1)/1.f;
            data_img[i*173056+j] = 1;
            data_img_count ++ ;
        }
    }
    std::cout << "data_img zero count is: " << zeroCount(data_img, data_img_len) << ". data_img_count: " << data_img_count << std::endl;

    for(int i=0; i<27; i++) {
        for(int j=0; j<173056; j++){
            data_in[i*173056+j] = 1;
        }
    }
    std::cout << "data_in zero count is: " << zeroCount(data_in, 27*416*416) << std::endl;

    for(int i=0; i<16; i++){
        for(int j=0; j<173056; j++){
            float tmp = rand()%255 + 100;
            data_out[i*173056 + j] = 0;
        }
    }

    std::cout << "data_out zero count is: " << zeroCount(data_out, 16*416*416) << std::endl;

    int count = 0;
    for(int i =0; i<16; i++) {
        for(int j=0; j<27; j++) {
            kernel_weights[i*27+j] = 1;
            count++;
        }
    }
    std::cout << "kernel_weights zero count is: " << zeroCount(kernel_weights, 16*27)<< std::endl;

    m_ResizedImage->m_DataArray = data_in;

    OCLManager *manager = new OCLManager();
    manager->Initialize();

    OCLBuffer *bufImg = manager->InitializeFloatArray(data_img, 3*416*416);
    PrintOCLBuffer(bufImg, manager, "bufImg_before.bin",  3*416*416);

    // after the InitializaFloatArray call, data stored in dataIn has been copied to variable buf which resides in gpu.
    OCLBuffer *bufImg9x = manager->InitializeFloatArray(data_in, 27*416*416);
    PrintOCLBuffer(bufImg9x, manager, "bufImg9x_before.bin",  27*416*416);

    // after the InitializaFloatArray call, data stored in data_out has been copied to variable databuf_out which resides in gpu.
    OCLBuffer *databuf_out = manager->InitializeFloatArray(data_out, 16*416*416);
    PrintOCLBuffer(databuf_out, manager, "databuf_out_before.bin",  16*416*416);

    OCLBuffer *weights_gpu = manager->InitializeFloatArray(kernel_weights, 16*27);
    PrintOCLBuffer(weights_gpu, manager, "weights_gpu.bin", 16*27);

    //float OCLManager::ConvertImageToColumnArray(OCLBuffer *im, int channels, int height, int width,
    //                                                int ksize, int stride, int pad, OCLBuffer *data_col)

    manager->ConvertImageToColumnArray(bufImg, 3, 416, 416, 3, 1, 1, bufImg9x);
    PrintOCLBuffer(bufImg9x, manager, "bufImg9x_after.bin",  27*416*416);

    int m = 16;
    int k = 27;
    int n = 416*416;

    manager->ComputeGEMM(false, false, m, 416*416, 27, 1.0f, weights_gpu, 0, k,
                           bufImg9x, 0, n , 1.0f, databuf_out, 0, n);

    PrintOCLBuffer(databuf_out, manager, "databuf_out_after.bin",  16*416*416);

//float OCLManager::ComputeGEMM(bool isATransponsed, bool isBTransposed, const size_t m, const size_t n, const size_t k,
//const float alpha, OCLBuffer *bufferA, const size_t offsetA, const size_t ldA, OCLBuffer *bufferB, const size_t offsetB, ldB,
//const float beta, OCLBuffer *bufferC, const size_t offsetC, const size_t ldC)




//    timeAccumulator += m_OCLManager->ConvertImageToColumnArray(netState->m_InputGpu, inLayer->m_C, inLayer->m_H,
//                inLayer->m_W, inLayer->m_Size, inLayer->m_Stride, inLayer->m_Pad, netState->m_Workspace);

//    timeAccumulator += m_OCLManager->ComputeGEMM(false, false, m, n, k, 1.0f, inLayer->m_Weights_Gpu, 0, k,
//                netState->m_Workspace, 0, n, 1.0f, inLayer->m_OutputSwapGPUBuffers[netState->m_ConvSwapBufIdx], 0, n);

    DEL_(data_img);
    DEL_(data_in);
    DEL_(data_out);
    DEL_(kernel_weights);
    DEL_(m_ResizedImage);
    DEL_(manager);
    DEL_(bufImg);
    DEL_(bufImg9x);
    DEL_(databuf_out);
    DEL_(weights_gpu);
}


/*
BOOST_AUTO_TEST_CASE(PassTest) {

    string	labelsFile = "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/coco.names";
    string	configFile = "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/tiny-yolo.cfg";
    string	weightsFile = "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/tiny-yolo.weights";
    string inputImage =  "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/pedestrians.jpg";

    int		enableDisplay = 1;
    int		saveOutput = 0;

    m_YOLODeepNNObj = new YOLONeuralNet(&labelsFile[0u], &configFile[0u], &weightsFile[0u], enableDisplay, saveOutput);
    m_YOLODeepNNObj->Initialize();
    m_YOLODeepNNObj->ComputeYOLONNOutput(&inputImage[0u]);

    m_YOLODeepNNObj->Finalize();
    delete m_YOLODeepNNObj;
    BOOST_CHECK_EQUAL(1,1);

}*/

