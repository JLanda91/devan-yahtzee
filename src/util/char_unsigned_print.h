#ifndef DEVAN_YAHTZEE_CHAR_UNSIGNED_PRINT_H
#define DEVAN_YAHTZEE_CHAR_UNSIGNED_PRINT_H

std::ostream& operator<<(std::ostream& os, const uint8_t& x){
	os << (unsigned)x;
	return os;
}

#endif //DEVAN_YAHTZEE_CHAR_UNSIGNED_PRINT_H
