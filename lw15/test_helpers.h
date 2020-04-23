#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <iostream>

typedef struct cout_redirect {
 private:
    std::streambuf* old;
 public:
    cout_redirect(std::streambuf* new_buffer) : old(std::cout.rdbuf(new_buffer)){}

    ~cout_redirect() { std::cout.rdbuf(old); }
} cout_redirect;

#define RESULT(X) std::cout << (X?"PASS":"FAIL") << ": " << __FUNCTION__ << std::endl;

#define FUNC_ARGS(X, Y, Z) #X, X, #Y, Y, __FUNCTION__, __LINE__

#define TRY(X,Y,Z,COND,FUNC) \
try {\
  if (COND) {\
    FUNC(FUNC_ARGS(X, Y, Z));\
    Z;\
  }\
} catch (const std::exception& err) {\
  std::cout << err.what() << std::endl;\
  Z;\
}
#define CHECK_EQ(X, Y, Z) TRY(X,Y,Z,!(X == Y),explain_eq)
#define EXPECT_EQ(X, Y) CHECK_EQ(X, Y, pass = false)
#define ASSERT_EQ(X, Y) CHECK_EQ(X, Y, RESULT(false); return false)

#define CHECK_NE(X, Y, Z) TRY(X,Y,Z,!(X != Y),explain_ne)
#define EXPECT_NE(X, Y) CHECK_NE(X, Y, pass = false)
#define ASSERT_NE(X, Y) CHECK_NE(X, Y, RESULT(false); return false)

#define CHECK_LT(X, Y, Z) TRY(X,Y,Z,!(X < Y),explain_lt)
#define EXPECT_LT(X, Y) CHECK_LT(X, Y, pass = false)
#define ASSERT_LT(X, Y) CHECK_LT(X, Y, RESULT(false); return false)

#define CHECK_LE(X, Y, Z) TRY(X,Y,Z,!(X <= Y),explain_le)
#define EXPECT_LE(X, Y) CHECK_LE(X, Y, pass = false)
#define ASSERT_LE(X, Y) CHECK_LE(X, Y, RESULT(false); return false)

#define CHECK_GT(X, Y, Z) TRY(X,Y,Z,!(X > Y),explain_gt)
#define EXPECT_GT(X, Y) CHECK_GT(X, Y, pass = false)
#define ASSERT_GT(X, Y) CHECK_GT(X, Y, RESULT(false); return false)

#define CHECK_GE(X, Y, Z) TRY(X,Y,Z,!(X >= Y), explain_ge)
#define EXPECT_GE(X, Y) CHECK_GE(X, Y, pass = false)
#define ASSERT_GE(X, Y) CHECK_GE(X, Y, RESULT(false); return false)

#define TRY_TF(X,Y,Z,COND) \
try {\
  if (COND) {\
    explain_tf(#X, X, Y, __FUNCTION__, __LINE__);\
    Z;\
  }\
} catch (const std::exception& err) {\
  std::cout << err.what() << std::endl;\
  Z;\
}
#define CHECK_TRUE(X, Y, Z) TRY_TF(X,Y,Z,!(X))
#define EXPECT_TRUE(X) CHECK_TRUE(X, true, pass = false)
#define ASSERT_TRUE(X) CHECK_TRUE(X, true, RESULT(false); return false)

#define CHECK_FALSE(X, Y, Z) TRY_TF(X,Y,Z,X)
#define EXPECT_FALSE(X) CHECK_FALSE(X, false, pass = false)
#define ASSERT_FALSE(X) CHECK_FALSE(X, false, RESULT(false); return false)

#define EXPECT_THROW(X) \
try {\
  X;\
  std::cout << "expected an exception, but nothing thrown" << std::endl;\
  EXPECT_FALSE(true);\
} catch (const std::exception& err) {}

#define ASSERT_THROW(X) \
try {\
  X;\
  std::cout << "expected an exception, but nothing thrown" << std::endl;\
  ASSERT_FALSE(true);\
} catch (const std::exception& err) {}

#define EXPECT_NO_THROW(X) \
try {\
  X;\
} catch (const std::exception& err) {\
  std::cout << "expected no exception, but got " << err.what() << std::endl;\
  EXPECT_TRUE(false);\
}

#define ASSERT_NO_THROW(X) \
try {\
  X;\
} catch (const std::exception& err) {\
  std::cout << "expected no exception, but got " << err.what() << std::endl;\
  ASSERT_TRUE(false);\
}

#define TF(X) (X?"true":"false")

#define STARTING(X) std::cout << "Starting test_" << #X << "..." << std::endl;
#define TEST(X) STARTING(X); test_##X() ? pass_cnt++ : fail_cnt++;
#define SKIP(X) std::cout << "Skipping test_" << #X << "..." << std::endl;

std::ostream& operator<<(std::ostream& os, std::nullptr_t) {
  os << "nullptr";
  return os;
}

template <typename T1, typename T2>
void explain_eq(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected equality of these values:" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T1, typename T2>
void explain_ne(
    const char n1[],
    const T1& o1,
    const char n2[],
    const T2& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected inequality of these values:" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

void explain_tf(
    const char name[],
    bool actual,
    bool expected,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Value of " << name << std::endl;
  std::cout << "  Actual: " << TF(actual) << std::endl;
  std::cout << " Expected: " << TF(expected) << std::endl;
}

template <typename T>
void explain_lt(
    const char n1[],
    const T& o1,
    const char n2[],
    const T& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be <" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T>
void explain_le(
    const char n1[],
    const T& o1,
    const char n2[],
    const T& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be <=" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T>
void explain_gt(
    const char n1[],
    const T& o1,
    const char n2[],
    const T& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be >" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

template <typename T>
void explain_ge(
    const char n1[],
    const T& o1,
    const char n2[],
    const T& o2,
    const char func[],
    const size_t line) {
  std::cout << func << ":" << line << ": Failure" << std::endl;
  std::cout << "Expected" << std::endl;
  std::cout << " " << n1 << std::endl;
  std::cout << "  Which is: " << o1 << std::endl;
  std::cout << "to be >=" << std::endl;
  std::cout << " " << n2 << std::endl;
  std::cout << "  Which is: " << o2 << std::endl;
}

#endif  // TEST_HELPERS_H
