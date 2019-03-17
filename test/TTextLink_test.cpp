#include <gtest/gtest.h>
#include "../include/TTextLink.h"

TEST(TTextLink, can_create_link)
{
    TTextLink::InitMemSystem(1);
    ASSERT_NO_THROW(new TTextLink((char *)"test"));
}