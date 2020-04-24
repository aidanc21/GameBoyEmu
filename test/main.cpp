#include "gtest/gtest.h"
#include "file_parser_tests.h"
#include "memory_map_tests.h"
#include "memory_tests.h"
#include "cpu_tests.h"
#include "cpu_alu_tests.h"
#include "cpu_registers_tests.h"
#include "cpu_jumps_tests.h"
#include "cpu_ld_tests.h"
#include "cpu_rotates_tests.h"
#include "cpu_misc_tests.h"
#include "cpu_bit_ops_tests.h"
#include "cpu_interrupts_tests.h"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}