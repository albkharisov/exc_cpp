namespace
{
    struct Test
    {
        std::string data = "123";
    };

    inline void foo() {

        int a = 52;
        int b[12] = {0};
        for (int i = 0; i < 12; ++i, a++)
        {
            b[i] = a*2;
        }
        std::string c = "r2r23r";
        if (b[a % 12])
            c += "124";
        else
            c = "17";
        std::cout << ((c == "17") ? "1 " : " 1") << std::endl;

        //std::cout << "1" << std::endl;
    }

    static void bar() { std::cout << "2" << std::endl; }

    void foobar() { std::cout << "3" << std::endl; }
}

