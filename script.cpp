#include "script.h"

#include <QDebug>


void Script::fOpenButton() {
    std::ifstream inDbg;
    inDbg.open(dbgName.toStdString().c_str());


    std::string line;
    while (std::getline(inDbg, line)) {
        if (line == "Dbg")
            continue;
        emit addLine(line);
    }
}
