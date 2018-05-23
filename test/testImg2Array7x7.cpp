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
using  namespace std;

#define DEL_(name) do { if( NULL != (name) ) { delete (name); (name) = NULL; } } while(0)


//YOLONeuralNet	*m_YOLODeepNNObj;

/*BOOST_AUTO_TEST_CASE(FailTest) {
    BOOST_CHECK_EQUAL(1,1);
}*/


BOOST_AUTO_TEST_CASE(kernel7x7) {
    StructImage	*m_ResizedImage = new StructImage();

    m_ResizedImage->m_C = 3;
    m_ResizedImage->m_H = 416;
    m_ResizedImage->m_W = 416;

    int flatNumIn = m_ResizedImage->m_C *  m_ResizedImage->m_H *  m_ResizedImage->m_W;
    int flatNumOut= m_ResizedImage->m_C *  m_ResizedImage->m_H *  m_ResizedImage->m_W;

    float *data_img = new float [3*416*416];
    float *data_in = new float [27*416*416];  // the input to GEMM will be 9 times bigger than data_img
    float *data_col = new float [flatNumOut];



    float *data_out= new float [16*416*416];
    float *kernel_weights = new float[16*27];

    for(int i =0; i<3; i++){
        for(int j=0; j<416*416; j++){
            data_img[i*3+j] = (i+1)/10.f;
        }

    }


    for(int i=0; i<27; i++) {
        for(int j=0; j<173056; j++){
            data_in[i*27+j] = (i+1)/10.0f;
        }
    }

    for(int i =0; i<16; i++) {
        for(int j=0; j<27; j++) {

            kernel_weights[i*16+j] = (i*10)/1.0f;
        }
    }




    m_ResizedImage->m_DataArray = data_in;

    OCLManager *manager = new OCLManager();
    manager->Initialize();

    OCLBuffer *bufImg = manager->InitializeFloatArray(data_in, 3*416*416);

    // after the InitializaFloatArray call, data stored in dataIn has been copied to variable buf which resides in gpu.
    OCLBuffer *bufImg9x = manager->InitializeFloatArray(data_in, 27*416*416);

    // after the InitializaFloatArray call, data stored in data_col has been copied to variable databuf_out which resides in gpu.
    OCLBuffer *databuf_out = manager->InitializeFloatArray(data_col, 16*416*416);

    OCLBuffer *weights_gpu = manager->InitializeFloatArray(kernel_weights, 16*27);


    //float OCLManager::ConvertImageToColumnArray(OCLBuffer *im, int channels, int height, int width,
    //                                                int ksize, int stride, int pad, OCLBuffer *data_col)

    manager->ConvertImageToColumnArray(bufImg, 3, 416, 416, 3, 1, 1, bufImg9x);


    int m = 16;
    int k = 27;
    int n = 416*416;


    manager->ComputeGEMM(false, false, 16, 173506, 27, 1.0f, weights_gpu, 0, k,
                           bufImg9x, 0, n , 1.0f, databuf_out, 0, n);

    PrintOCLBuffer(databuf_out, manager, "databuf_out.bin",  16*416*416);



/*
float OCLManager::ComputeGEMM(bool isATransponsed, bool isBTransposed, const size_t m, const size_t n, const size_t k,
const float alpha, OCLBuffer *bufferA, const size_t offsetA, const size_t ldA, OCLBuffer *bufferB, const size_t offsetB, ldB,
const float beta, OCLBuffer *bufferC, const size_t offsetC, const size_t ldC)
*/


/*
    timeAccumulator += m_OCLManager->ConvertImageToColumnArray(netState->m_InputGpu, inLayer->m_C, inLayer->m_H,
                inLayer->m_W, inLayer->m_Size, inLayer->m_Stride, inLayer->m_Pad, netState->m_Workspace);

    timeAccumulator += m_OCLManager->ComputeGEMM(false, false, m, n, k, 1.0f, inLayer->m_Weights_Gpu, 0, k,
                netState->m_Workspace, 0, n, 1.0f, inLayer->m_OutputSwapGPUBuffers[netState->m_ConvSwapBufIdx], 0, n);
*/


    DEL_(data_in);
    DEL_(data_col);
    DEL_(data_out);
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

