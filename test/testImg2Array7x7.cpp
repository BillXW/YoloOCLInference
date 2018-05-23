//
// Created by ubuntu on 5/22/18.
//

#define BOOST_TEST_MODULE image2Array7x7Tests

#include <boost/test/unit_test.hpp>

#include "OCLManager.h"
#include <limits.h>
#include <unistd.h>
#include "buffer.h"
#include "YoloOCLDNN.h"

YOLONeuralNet	*m_YOLODeepNNObj;

BOOST_AUTO_TEST_CASE(FailTest) {
    BOOST_CHECK_EQUAL(1,2);
}

BOOST_AUTO_TEST_CASE(PassTest) {

    string	labelsFile = "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/coco.names";
    string	configFile = "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/tiny-yolo.cfg";
    string	weightsFile = "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/tiny-yolo.weights";
    char inputImage[PATH_MAX] =  "/home/ubuntu/zhangchao/cvs/YoloOCLInference/data/pedestrians.jpg";

    int		enableDisplay = 1;
    int		saveOutput = 0;

    m_YOLODeepNNObj = new YOLONeuralNet(&labelsFile[0u], &configFile[0u], &weightsFile[0u], enableDisplay, saveOutput);
    m_YOLODeepNNObj->Initialize();
    m_YOLODeepNNObj->ComputeYOLONNOutput(inputImage);

    m_YOLODeepNNObj->Finalize();
    delete m_YOLODeepNNObj;
    BOOST_CHECK_EQUAL(1,1);
}

