#include "stdafx.h"
#include "CTable.h"
#include <stdexcept>

CTable::CTable()
{
	rows = 0;
	columns = 0;
	rowHeight = 70;
	offsetX = 10;
	offsetY = 10;
	fontSize = 16;
}

CTable::CTable(const std::string& sName, int columns, int rows,int colsWidth)
{
	if (columns < 0 || rows < 0)
		throw std::invalid_argument("Count columns and rows should be >= 0");
	this->name = sName.c_str();
	this->columns = columns;
	this->rows = rows;
	types.resize(columns);
	rowHeight = 20;
	offsetX = 10;
	offsetY = 10;
	columnWidths.assign(columns, colsWidth);
	fontSize = 16;
}

CTable& CTable::addRow()
{
	return *this;
}

CTable& CTable::addColumn(std::string title, type colType, int width)
{
	if (rows) {
		if (colType == INT) {
			for (int i = 0; i < rows; i++) {
				table[columns][i] = std::make_unique<IntCell>();
			}
		}
		else if (colType == DOUBLE) {
			for (int i = 0; i < rows; i++) {
				table[columns][i] = std::make_unique<DoubleCell>();
			}
		}
		else if (colType == STRING) {
			for (int i = 0; i < rows; i++) {
				table[columns][i] =std::make_unique<StringCell>();
			}
		}
		else if (colType == IMG) {
			for (int i = 0; i < rows; i++) {
				table[columns][i] = std::make_unique<ImgCell>();
			}
		}
		else {
			return *this;
		}
	}
	titles.push_back(title);
	columnWidths.push_back(width);
	types.push_back(colType);
	columns++;
	return *this;
}

CTable& CTable::draw(CDC* pDC)
{
	CFont font;
	font.CreatePointFont(fontSize * 10, L"Arial");
	pDC->SelectObject(&font);
	int colWidth = 0;
	for (int i = 0; i < columns; i++) {
		colWidth += columnWidths[i];
	}
	CRect rect(offsetX, offsetY, offsetX + colWidth, offsetY + rowHeight);
	pDC->Rectangle(rect);
	pDC->DrawText(CString(name.c_str()), rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	int colOffset = offsetX;
	int rowOffset = offsetY+rowHeight;
	for (int i = 0; i < columns; i++) {
		CRect headerRect(colOffset, rowOffset, colOffset + columnWidths[i], rowOffset + rowHeight);
		pDC->Rectangle(headerRect);
		pDC->DrawText(CString(titles[i].c_str()), headerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		colOffset += columnWidths[i];
	}
	return *this;
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			//table[i][j]->draw();
		}
	}
}

void IntCell::draw(CDC* pDC,CRect& rect)
{
	CString str;
	str.Format(L"%d", value);
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void DoubleCell::draw(CDC* pDC, CRect& rect)
{
	CString str;
	str.Format(L"%f", value);
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void StringCell::draw(CDC* pDC, CRect& rect)
{
	CString str(value.c_str());
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void ImgCell::draw(CDC* pDC, CRect& rect)
{
	CImage img;
	img.Load(CString(path.c_str()));
	img.Draw(pDC->m_hDC, rect);
}