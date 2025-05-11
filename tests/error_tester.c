// error_tester.c - Test Wisp logger error output and interpreter error handling
#include "../src/modules/logger.h"
#include "../src/modules/symbol_table.h"
#include "../src/modules/interpreter.h"
#include <stdio.h>

int main(void)
{
    // Test logger error output
    WISP_LOGE("This is a test error message.");
    WISP_LOGW("This is a test warning message.");
    WISP_LOGI("This is a test info message.");
    WISP_LOGD("This is a test debug message.");
    WISP_LOGS("This is a test success message.");
    WISP_LOGT("This is a test trace message.");

    // Test full error template
    WISP_LOGE_FULL(
        "E9999", "TestError", "error_tester.c",
        "This is a simulated error for testing.",
        "This error is for logger and error template validation.",
        "    - Check your logger integration.\n    - Review error formatting.",
        "https://wisp-lang.org/docs/errors");

    // Test interpreter error (no source)
    int interp_result = wisp_interpret(NULL, "test.wisp");
    printf("Interpreter returned: %d\n", interp_result);

    return 0;
}
