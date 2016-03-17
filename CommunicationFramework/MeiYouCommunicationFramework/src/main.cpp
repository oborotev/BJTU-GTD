# include "TaiTaiP2PClient.h"

int main() {
    TaiTaiP2PClient test("10.42.0.1", 5000);

    if (test.client() == TaiTaiP2PClient::States::ERROR)
        return 1;
    return 0;
}