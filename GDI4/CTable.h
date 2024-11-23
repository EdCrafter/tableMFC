#pragma once
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class Cell
{
public:
	Cell() {};
	virtual void draw(CDC* pDC,CRect& rect) =0;
	virtual ~Cell() = default;
	virtual void setValue(void* value) = 0;
};

class IntCell : public Cell
{
	int value;
public:
	IntCell(int val=0) : value(val) {}
	void draw(CDC* pDC,CRect& rect) override;
	void setValue(void* value) override {
		if (!value) {
			throw std::invalid_argument("IntCell requires a valid pointer");
		}
		this->value = *static_cast<int*>(value);
	}
};

class DoubleCell : public Cell
{
	double value;
public:
	DoubleCell(double val=0) : value(val) {}
	void draw(CDC* pDC,CRect& rect) override;
	void setValue(void* value) override {
		if (!value) {
			throw std::invalid_argument("DoubleCell requires a valid pointer");
		}
		this->value = *static_cast<double*>(value);
	}
};

class StringCell : public Cell
{
	std::string value;
public:
	StringCell(std::string val="") : value(val) {}
	void draw(CDC* pDC,CRect& rect) override;
	void setValue(void* value) override {
		if (!value) {
			throw std::invalid_argument("StringCell requires a valid pointer");
		}
		this->value = *static_cast<std::string*>(value);
	}
};

class ImgCell : public Cell
{
	std::string path;
public:
	ImgCell(std::string path="") : path(path) {}
	void draw(CDC* pDC,CRect& rect) override;
	void setValue(void* value) override {
		if (!value) {
			throw std::invalid_argument("ImgCell requires a valid pointer");
		}
		this->path = *static_cast<std::string*>(value);
	}
};



class CTable
{
public:
	enum type { INT, DOUBLE, STRING, IMG };
private:
	std::string name;
	int columns;
	int rows;
	std::vector<std::vector<std::unique_ptr<Cell>>> table;
	std::vector<std::string> titles;
	std::vector<type> types;
	int offsetX, offsetY;
	std::vector<int> columnWidths;
	int rowHeight;
	int fontSize;
public:
	
	CTable();
	CTable(const std::string& sName, int columns = 1, int rows = 1, int colsWidth = 100);
	CTable& addRow();
	CTable& addColumn(std::string title, type colType, int width = 200);
	CTable& setName(std::string sName) { name = sName; return *this;};
	CTable& setOffsets(int x = 10, int y = 10) { offsetX = x; offsetY = y; return *this;};
	CTable& setColumnWidth(int col, int width = 100) { if (col >= 0 && width>0) columnWidths[col] = width; return *this; }
	CTable& setRowHeight(int height = 20) { if (height > 0) rowHeight = height; return *this; };
	CTable& setColumnTitle(int col, std::string title) { if (col >= 0) titles[col] = title; return *this; }
	CTable& draw(CDC* pDC);
	std::vector < std::unique_ptr<Cell>>& operator[](int col) { return table[col]; }
	CTable& CTable::setCell(int row, int col, void* value) {
		if (row >= rows || col >= columns) {
			throw std::out_of_range("Cell index out of bounds");
		}
		table[col][row]->setValue(value);
		return *this;
	}

	CTable& addRow(const std::vector<void*>& values);
};

