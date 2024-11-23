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
	table.resize(columns);
	for (int i = 0; i < columns; i++) {
		table[i].resize(rows);
	}
}

CTable& CTable::addRow() {
	if (table.size() != columns) {
		table.resize(columns);
	}
	for (int i = 0; i < columns; i++) {
		if (table[i].size() < rows + 1) {
			table[i].resize(rows + 1); 
		}
		if (types[i] == INT) {
			table[i][rows] = std::make_unique<IntCell>();
		}
		else if (types[i] == DOUBLE) {
			table[i][rows] = std::make_unique<DoubleCell>();
		}
		else if (types[i] == STRING) {
			table[i][rows] = std::make_unique<StringCell>();
		}
		else if (types[i] == IMG) {
			table[i][rows] = std::make_unique<ImgCell>();
		}
		else {
			throw std::runtime_error("Unknown column type in addRow");
		}
	}
	rows++;
	return *this;
}


CTable& CTable::addColumn(std::string title, type colType, int width)
{
	if (columns >= table.size()) {
		table.resize(columns + 1);
	}
	table[columns].resize(rows);
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
	pDC->MoveTo(colOffset, rowOffset);
	pDC->LineTo(colOffset, rowOffset + rowHeight);
	for (int i = 0; i < columns; i++) {
		CRect headerRect(colOffset, rowOffset, colOffset + columnWidths[i], rowOffset + rowHeight);
		pDC->MoveTo(colOffset, rowOffset + rowHeight);
		pDC->LineTo(colOffset + columnWidths[i], rowOffset + rowHeight);
		pDC->LineTo(colOffset + columnWidths[i], rowOffset);
		pDC->DrawText(CString(titles[i].c_str()), headerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		colOffset += columnWidths[i];
	}


	for (int i = 0; i < rows; i++) {
		colOffset = offsetX;
		rowOffset = offsetY + (2+i)*rowHeight;
		pDC->MoveTo(colOffset, rowOffset);
		pDC->LineTo(colOffset, rowOffset + rowHeight);
		for (int j = 0; j < columns; j++) {
			pDC->MoveTo(colOffset, rowOffset + rowHeight);
			pDC->LineTo(colOffset + columnWidths[j], rowOffset + rowHeight);
			pDC->LineTo(colOffset + columnWidths[j], rowOffset);
			CRect cellRect(colOffset, rowOffset, colOffset + columnWidths[j], rowOffset + rowHeight);
			table[j][i]->draw(pDC, cellRect);
			colOffset += columnWidths[j];
		}
	}
	return *this;
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
	str.Format(L"%0.2f", value);
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void StringCell::draw(CDC* pDC, CRect& rect)
{
	CString cstr(value.c_str());
	pDC->DrawText(cstr, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void ImgCell::draw(CDC* pDC, CRect& rect)
{
	CImage img;
	HRESULT hr = img.Load(CString(path.c_str()));

	if (FAILED(hr)) {

		std::wstring wPath(path.begin(), path.end());
		CString errorMsg;
		errorMsg.Format(L"Image load failed: %s", wPath.c_str());
		rect.left += 10;
		pDC->DrawText(errorMsg, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		return;
	}
	img.Draw(pDC->m_hDC, rect);

}

CTable& CTable::addRow(const std::vector<void*>& values) {
	// Проверяем, что количество значений соответствует количеству столбцов
	if (values.size() != columns) {
		throw std::invalid_argument("Values count should be equal to columns count" + std::to_string(columns) + " but was " + std::to_string(values.size()));
	}

	// Увеличиваем количество строк
	rows++;

	// Для каждого столбца проверяем, что достаточно строк в векторе
	for (int i = 0; i < columns; i++) {
		if (table[i].size() <= rows) {
			// Увеличиваем размер столбца, если это необходимо
			if (types[i] == INT) {
				table[i].push_back(std::make_unique<IntCell>());
			}
			else if (types[i] == DOUBLE) {
				table[i].push_back(std::make_unique<DoubleCell>());
			}
			else if (types[i] == STRING) {
				table[i].push_back(std::make_unique<StringCell>());
			}
			else if (types[i] == IMG) {
				table[i].push_back(std::make_unique<ImgCell>());
			}
			else {
				throw std::runtime_error("Unknown column type in addRow");
			}
		}
	}

	// Записываем значения в ячейки для текущей строки
	for (int i = 0; i < columns; i++) {
		if (table[i][rows - 1] == nullptr) {
			throw std::runtime_error("Cell is nullptr at row " + std::to_string(rows) + " and column " + std::to_string(i));
		}

		// Устанавливаем значение в ячейку
		table[i][rows - 1]->setValue(values[i]);
	}

	return *this;
}

