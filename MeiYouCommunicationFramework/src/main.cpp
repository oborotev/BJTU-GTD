# include "TaiTaiP2PClient.h"

int main() {
    TaiTaiP2PClient test("192.168.1.106", 56002);

    if (test.client() == TaiTaiP2PClient::States::ERROR)
        return 1;
    return 0;
}