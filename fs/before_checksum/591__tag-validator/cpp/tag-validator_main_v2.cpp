int main() {
    std::vector<std::string> tests = {
        "<A></A>",
        "<A>TEXT</A>",
        "<A><![CDATA[xyz]]></A>",
        "<A><B>HELLO</B><C></C></A>",
        "<TAG><INNERA><![CDATA[<not>parsed</not>]]></INNERA><INNERB>DATA</INNERB></TAG>",
        "<ABCDEFGHI></ABCDEFGHI>",
        "<OUT>pre<B>mid</B>post</OUT>",
        "<X>t1<![CDATA[abc]]>t2<B></B>t3</X>",
        "<A><B><C><D></D></C></B></A>",
        "<ROOT>123<![CDATA[<tag>]]>456</ROOT>"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        checksum += sol.isValid(tests[0]);
        checksum += sol.isValid(tests[1]);
        checksum += sol.isValid(tests[2]);
        checksum += sol.isValid(tests[3]);
        checksum += sol.isValid(tests[4]);
        checksum += sol.isValid(tests[5]);
        checksum += sol.isValid(tests[6]);
        checksum += sol.isValid(tests[7]);
        checksum += sol.isValid(tests[8]);
        checksum += sol.isValid(tests[9]);
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}