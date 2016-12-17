#include "operators.hpp"
#include <gtest/gtest.h>
#include <map>

TEST (calculate_centroid, operators) {
    operators t_operators;
    // clang-format off
    /* centroid at {1, 1} */
    //1  2
    //3  4
    std::map<unsigned int, keypoint_t> shape_a = {
        { 1, { 0, 2 } }, { 2, { 2, 2 } },
        { 3, { 0, 0 } }, { 4, { 2, 0 } }
    };
    /* centroid at {0.5, 0.5} */
    //1  2
    //3  4
    std::map<unsigned int, keypoint_t> shape_a_f = {
        { 1, { 0, 1 } }, { 0, { 1, 1 } },
        { 3, { 0, 0 } }, { 4, { 1, 0 } }
    };
    /* centroid at {2, 2} */
    //  1
    //2   3
    std::map<unsigned int, keypoint_t> shape_b = {
              { 1, { 2, 4 } },
        { 2, { 1, 1 } }, { 3, { 3, 1 } }
    };
    /* empty shape */
    std::map<unsigned int, keypoint_t> shape_empty = {
    };
    // clang-format on
    /* shape to limit */
    unsigned int shape_limit_points = 40;
    std::map<unsigned int, keypoint_t> shape_limit = {};
    for (unsigned int i = 1; i <= shape_limit_points; i++) {
        shape_limit.insert ({ i, { 65535, 65535 } });
    }
    /* shape A */
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_a).x, 1);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_a).y, 1);
    /* shape A float */
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_a_f).x, 0.5);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_a_f).y, 0.5);
    /* shape B */
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_b).x, 2);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_b).y, 2);
    /* shape empty */
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_empty).x, 0);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_empty).y, 0);
    /* shape limit */
    ASSERT_FLOAT_EQ (shape_limit.size (), shape_limit_points);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_limit).x, 65535);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_limit).y, 65535);
    /* shape over limit */
    shape_limit.insert (
    { shape_limit_points + 1, { 65535, 65535 } }); // over limit
    ASSERT_FLOAT_EQ (shape_limit.size (), shape_limit_points + 1);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_limit).x, 0);
    ASSERT_FLOAT_EQ (t_operators.calculate_centroid (shape_limit).y, 0);
}
