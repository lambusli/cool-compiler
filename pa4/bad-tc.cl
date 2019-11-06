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
