#include <iostream>
#include <fstream>
#include <sstream>
#include "src/Course.h"
#include "src/Terminal.h"
#include "src/Auxiliar.h"

int main() {
    Course leic = Course();
    Auxiliar::readClassesPerUc(leic);
    Auxiliar::readStudentsClasses(leic);
    Auxiliar::readClasses(leic);
    Terminal terminal = Terminal(leic);
    terminal.run();
    return 0;
}
