// testing the normalize_angle() function
void test_normalize_angle_no_change(); 
void test_normalize_angle_negative_angle();
void test_normalize_angle_large_negative();
void test_normalize_angle_over_angle();
void test_normalize_angle_large_positive();
void test_normalize_angle_edge_cases(); // 0 & 2 * M_PI

// testing the complex_num_init() function
void test_complex_num_init_error();
void test_complex_num_init_both_pos();
void test_complex_num_init_posneg();
void test_complex_num_init_negpos();
void test_complex_num_init_both_neg();

// testing complex_num_rev_init() & complex_num_empty() functions
void test_complex_num_rev_error();
void test_complex_num_rev();
void test_complex_num_empty();

// testing print functions
void test_complex_write_read_rect();
void test_complex_write_read_pol();
void test_complex_write_read_exp();
void test_complex_write_read();

// testing arithmetic functions
void test_complex_scale();
void test_complex_add();
void test_complex_sub();
void test_complex_prod();
void test_complex_pow();
void test_complex_inv();
void test_complex_div();
void test_complex_conj();