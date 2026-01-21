int main() {
    vector<string> tests = {
        "1 # # ",
        "2 1 # # 3 # # ",
        "4 3 2 1 # # # # # ",
        "1 # 2 # 3 # 4 # # ",
        "1 2 4 # # 5 # # 3 6 # # 7 # # ",
        "-10 -20 -30 # # -5 # # 15 0 # # 22 # # ",
        "1 1 1 # # # 1 1 # # 1 # # ",
        "8 4 2 1 # # 3 # # 6 5 # # 7 # # 12 10 9 # # 11 # # 14 13 # # 15 # # ",
        "5 2 # 3 # # 9 # 10 8 # # # ",
        "1 # 2 3 # 4 5 # # # # "
    };

    Codec codec;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            TreeNode* root = codec.deserialize(s);
            string s2 = codec.serialize(root);
            checksum += static_cast<int>(s2.size());
            freeTree(root);
        }
        sink = checksum;
    }

    return 0;
}