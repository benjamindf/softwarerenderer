#define CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS
#include "targa.hpp"
#include <catch.hpp>
#include <fstream>

TEST_CASE("targa", "[targa io]")
{
    Buffer2D<Targa::TargaFormat> imageBuffer(100, 100);

    SECTION("Clear Red targa")
    {
        Targa::TargaFormat red{ 255, 0, 0 };
        imageBuffer.clear(red);

        REQUIRE(imageBuffer.get(0, 0) == red);
        std::fstream f;
        //f.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        f.open("images/targa_clear_red.tga");

        REQUIRE(f.good());
        REQUIRE_NOTHROW(f <<= imageBuffer);
        f.seekg(0);
        f.seekp(0);

        Buffer2D<Targa::TargaFormat> fromFile = Targa::read(f);
        REQUIRE(fromFile.width() == 100);
        REQUIRE(fromFile.height() == 100);

        Targa::TargaFormat expected{ 255, 0, 0 };
        Targa::TargaFormat found = fromFile.get(0, 0);
        CHECK(found.r == expected.r);
        CHECK(found.g == expected.g);
        CHECK(found.b == expected.b);

        Targa::TargaFormat white = Targa::TargaFormat{ 255, 255, 255 };
        REQUIRE(glm::vec3(1, 1, 1) == static_cast<glm::vec3>(white));
    }
}
