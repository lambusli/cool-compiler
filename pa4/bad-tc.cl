class Queen {
    xq1 : Int <- (new Undef);
};

class King inherits Queen {};

class A {
    tempK : King;
    tempQ : Queen;
    xA1 : Int <- (tempK <- tempQ); -- You cannot assign sth superior to sth inferior
    xA2 : Int <- (xA1 <- undef);
    xA3 : Int <- (if 5 then 5 else 3 fi);
};

class Test {};

class LetTest inherits Test {
    xL3 : Int <- (let s : SELF_TYPE <- (new Blah) in true);
    xL4 : Int <- (let s : Undef <- 5 in true);
    xL5 : Int <- (let s : SELF_TYPE <- (new Test) in true);
};

class Un {
    xU1 : Int <- {
        ~(if true then 5 else 10 fi);
        ~(if true then 5 else "10" fi);
    };
};
