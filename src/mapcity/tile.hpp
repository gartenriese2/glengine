#ifndef _TILE_
#define _TILE_

class Tile {

	public:

		Tile(unsigned int, unsigned int);

		unsigned int X() const { return m_x; }
		unsigned int Y() const { return m_y; }

	private:

		unsigned int m_x;
		unsigned int m_y;

};

inline bool operator==(const Tile & lhs, const Tile & rhs) {
	return lhs.X() == rhs.X() && lhs.Y() == rhs.Y();
}
inline bool operator!=(const Tile & lhs, const Tile & rhs) {
	return !(lhs == rhs);
}

#endif // _TILE_
