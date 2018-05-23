//
// Created by ubuntu on 5/22/18.
//

#define BOOST_TEST_MODULE image2Array7x7Tests

#include <boost/test/unit_test.hpp>

#include "OCLManager.h"
#include <limits.h>
#include <unistd.h>
#include "buffer.h"

BOOST_AUTO_TEST_CASE(FailTest) {
    BOOST_CHECK_EQUAL(1,2);
}

BOOST_AUTO_TEST_CASE(PassTest) {
    BOOST_CHECK_EQUAL(1,1);
}

