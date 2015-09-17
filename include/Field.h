#ifndef _FIELD_
#define _FIELD_

class Field {
	private:
		const int DEFAULT_DIM = 10;
		bool **data;
		int cols, rows;
		bool stable;
	public:
		/* Constructor
		 *
		 * Takes the size of the field (rows x cols)
		 * and allocates memory for it.
		 * */
		Field(const int & _cols = DEFAULT_DIM, 
		      const int & _rows = DEFAULT_DIM) : cols {_cols}, rows {_rows}, stable {false};
		/* Set manually a cell to alive.
		 * */
		void setAlive(vector<pair<int, int> >);
		void setAlive(const int & row, const int & col);
		/* Verify if the field is stable
		 * */
		bool stable() const;
		/* Update field's state.
		 * */
		void update();
		/* Print field.
		 * */
		void print() const;
};

#endif
