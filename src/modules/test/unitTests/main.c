#include "../testdll.h"
#include <assert.h>

void testAssertionFail(){
    assert(("testAssertionFail", 0));
}

void testIfInstanceIsCreated(){
    void* instance = NULL;
    uint8_t* parameters;
    *parameters = 0;

    create(&instance, parameters);

    assert(("testIfInstanceIsCreated", instance));
}

int main()
{
    //testAssertionFail();
    printf("testIfInstanceIsCreated: ");
    testIfInstanceIsCreated();
    printf("OK");
    return 0;
}
