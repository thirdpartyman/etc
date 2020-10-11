#pragma once

//#define trycatch(expression) try { expression; } catch(std::exception e){puts(e.what());}

#define trycatch(expression) try { expression; } catch(...){}
#define tryend catch(...){}
#define trythrow(expression)\
    try\
    {\
    expression\
    }\
    catch (std::exception e)\
    {\
        throw e;\
    }