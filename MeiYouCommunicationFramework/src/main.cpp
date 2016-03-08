# include "TaiTaiP2PClient.h"

int main() {
    TaiTaiP2PClient test("127.0.0.1", 56000);

    if (test.client() == TaiTaiP2PClient::States::ERROR)
        return 1;
    return 0;
}