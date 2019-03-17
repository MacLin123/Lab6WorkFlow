#include <gtest/gtest.h>
#include "../include/TText.h"
TEST(TText, copy_has_its_own_memory)
{
    TTextLink::InitMemSystem(3);
    PTTextLink pl = new TTextLink((char *)"copy", NULL, NULL);
    TText t1(pl);
    PTText cpy = t1.getCopy();
    EXPECT_NE(&t1, cpy);
}
TEST(TText, can_getcopy)
{
    TTextLink::InitMemSystem(3);
    PTTextLink pl = new TTextLink((char *)"copy", NULL, NULL);
    TText t1(pl);
    PTText cpy = t1.getCopy();
    string s = t1.GetLine();
    s = cpy->GetLine();
    EXPECT_EQ(t1.GetLine(), cpy->GetLine());
}