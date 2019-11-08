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
    xA4 : Undef;
    fA1(argc : King) : SELF_TYPE {argc}; 
};

class Test {
    s : String;
    t : SELF_TYPE;
    t2 : LetTest;
    r1 : Int;
    r2 : String;
    xT0 : Int <- {
        --t <- (new SELF_TYPE);
        t <- (new LetTest);
        t2 <- (new SELF_TYPE);
    };
    xT1 : Int <- (let s : SELF_TYPE <- (new LetTest) in s);
    xT3 : Int <- (let tar : Int, s : SELF_TYPE <- (new LetTest) in (s));
};

class LetTest inherits Test {
    xL0 : Int <- {
        t2 <- (new SELF_TYPE);
    };
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

class Bin {
    --xBin1 : Int <- {3 + 4; 3 - 4; 3 * 4; 3 / 4;};
    xBin2 : Int <- {
        true + true;
        true < true;
        true <= true;
        true = 2;
        true = "bc";
        2 = " bc";
        (new Queen) = "a";
    };
};
