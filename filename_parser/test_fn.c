// This is a test program to verify the operation of the filename parser.

#include <stdio.h>
#include "filename.h"
#include <string.h>

// count of the number of failed tests
int errors = 0;

void fail(char * msg)
{
    printf("error: %s\n", msg);
    ++errors;
}

void test(char * name, 
          bool absolute, 
          int numPathParts,
          char ** pathParts)
{
    struct Pathname pn;
    printf("testing %s\n", name);
    bool ok = parseFullFilename(&pn, name);
    if (!ok) fail("valid name expected");
    if (absolute != pn.isAbsolute) fail("incorrect absolute");
    if (numPathParts != pn.numPathComponents) {
        char msg[1200];
        sprintf(msg, "expected %d path components but got %d", 
                numPathParts,
                pn.numPathComponents);
        fail(msg);
    }
    if (numPathParts != 0 && pn.pathComponents == NULL) {
        fail("pathComponents is null");
        return;
    }
    if (numPathParts == 0 && pn.pathComponents != NULL) {
        fail("pathComponents is not null");
        return;
    }
    for (int i=0; i<numPathParts; ++i) {
        if (pathParts[i] == NULL) fail("test error 1");
        if (pn.pathComponents[i] == NULL) fail("missing path component");
        if (strcmp(pathParts[i], pn.pathComponents[i]) != 0) {
            char msg[1200];
            sprintf(msg, "at %d expected %s but got %s", i, pathParts[i],
                    pn.pathComponents[i]);
            fail(msg);
        }
    }
}

void doValidTests()
{
    char * expect_a[] = {"a"};
    test("a", false, 1, expect_a);
    char * expect_abcd[] = {"abcd"};
    test("abcd", false, 1, expect_abcd);

    char * expect_a_b[] = {"a", "b"};
    test("a/b", false, 2, expect_a_b);
    test("/a/b", true, 2, expect_a_b);

    char * expect_a_b_c_d[] = {"aaa", "bbb", "ccc", "ddd"};
    test("aaa/bbb/ccc/ddd", false, 4, expect_a_b_c_d);

    // 255 character name is ok
    char * expect_big[] = {
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345",
    };
    test("12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345",
       false, 1, expect_big);

    char * expect_deep[] = {"1", "2", "3", "4", "5", "6", 
       "7", "8", "9", "0", "1", "2", "3", "4", "5", "6"};
    test("/1/2/3/4/5/6/7/8/9/0/1/2/3/4/5/6", true, 16, expect_deep);
}

void bad(char * name)
{
    struct Pathname pn;
    printf("testing %s\n", name);
    bool ok = parseFullFilename(&pn, name);
    if (ok) fail("error not detected in bad name");
}

void doInvalidTests()
{
   printf("starting test of invalid names\n");
   bad("//a");
   bad("a//b");
   bad("a//");
   bad("a/");

   // 256 character base name is bad
   bad("12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "123456");

   // 256 character path name is bad
   bad("12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "12345678901234567890123456789012345678901234567890"
       "123456"
       "/xxx");
   // too many directories
   bad("1/2/3/4/5/6/7/8/9/0/1/2/3/4/5/6/7");
}

int main()
{
    doValidTests();
    doInvalidTests();
    printf("total errors detected: %d\n", errors);
    return errors;
}
