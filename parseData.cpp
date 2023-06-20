#include "parseData.h"


void parseData::parser() {
    sData = QString(data);
    QString resultStr = nullptr;

/* здесь в будущем будут разбираться входные данные в зависимости от режима работы, пока
 * режим только один State::SimpleOut
*/
    for (auto ch : sData) {
        switch (state){
        case State::Empty:
            break;
        case State::SimpleOutput:
            resultStr.append(ch);
            break;
        case State::ReadMem:
            break;
        case State::WriteMem:
            break;
        case State::ReadPort:
            break;
        case State::WritePort:
            break;
        case State::ReadFile:
            break;
        case State::WriteFile:
            break;
        case State::Jump:
            break;

        }
    }
    emit showData(resultStr);
}
