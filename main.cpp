#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>

#include "tjs.h"
#include "tjsError.h"

int main() {
    tTJS *tjsengine = new tTJS();

    std::string filePath = "../test.js";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "打开文件失败: " << filePath << std::endl;
        return 1;
    }

    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;

    // 执行转换


    std::stringstream buffer;
    buffer << file.rdbuf(); // 将文件内容读取到stringstream

    std::string content = buffer.str();

    std::u16string utf16String = converter.from_bytes(content);

    tjs_char *script = new tjs_char(content.length());
    TJS_mbstowcs(script, content.c_str(), 0);
    try {
        tTJSVariant result; // 結果を受け取るための変数

        tjsengine->ExecScript(utf16String.c_str(), &result, NULL,TJS_W("test code")); // テストスクリプトを実行

        printf("result : %lld\n", (tTVInteger) result); // 結果を表示
    } catch (eTJSError &e) {
        printf("error: %ls\n", e.GetMessage().c_str());
    }
    catch (...) {
        printf("エラーが発生しました\n");
    }

    tjsengine->Shutdown(); // TJS2 スクリプトエンジンをシャットダウン
    tjsengine->Release(); // TJS2 スクリプトエンジンを解放

    return 0;
}
