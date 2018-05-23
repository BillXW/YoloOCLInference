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

    float *data_in = new float [flatNumIn];
    float *data_col = new float [flatNumOut];

    for(int i = 0; i<flatNumOut; i++) {
        data_col[i] = 999;
    }


    m_ResizedImage->m_DataArray = data_in;

    OCLManager *manager = new OCLManager();
    manager->Initialize();

    OCLBuffer *buf = manager->InitializeFloatArray(data_in, sizeof(float));


    OCLBuffer *databuf = manager->InitializeFloatArray(data_col, sizeof(float));

    //float OCLManager::ConvertImageToColumnArray(OCLBuffer *im, int channels, int height, int width,
    //                                                int ksize, int stride, int pad, OCLBuffer *data_col)

    manager->ConvertImageToColumnArray(buf, 3, 416, 416, 3, 1, 1, databuf);

    
/*
float OCLManager::ComputeGEMM(bool isATransponsed, bool isBTransposed, const size_t m, const size_t n, const size_t k,
const float alpha, OCLBuffer *bufferA, const size_t offsetA, const size_t ldA, OCLBuffer *bufferB, const size_t offsetB, ldB,
const float beta, OCLBuffer *bufferC, const size_t offsetC, const size_t ldC)
*/


    for(int i= 0; i< 100; i++) {
        std::cout << data_col[i] << std::endl;
    }

    DEL_(data_in);
    DEL_(data_col);
    DEL_(m_ResizedImage);
    DEL_(manager);
    DEL_(buf);
    DEL_(databuf);


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

