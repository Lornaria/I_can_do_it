#include "parsetext.h"

ParseText::ParseText(QString txt)
{
    str = txt;
}

QString ParseText::parse(){
    if(str == "руб"){
        str = "₽";
    }
    else if(str == "с"){
        str = "©";
    }
    else if(str == "пр"){
        str = "‰";
    }
    else if(str == "р"){
        str = "®";
    }
    return str;
}
