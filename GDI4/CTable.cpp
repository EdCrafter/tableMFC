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
	font.CreatePointFont(160, L"Arial");
}

CTable::CTable(const std::string& sName, int columns, int rows,int colsWidth)
{
	if (columns < 0 || rows < 0)
		throw std::invalid_argument("Count columns and rows should be >= 0");
	this->name = sName.c_str();
	this->columns = columns;
	this->rows = rows;
	types.resize(columns);
	rowHeight = 70;
	offsetX = 10;
	offsetY = 10;
	columnWidths.assign(columns, colsWidth);
	font.CreatePointFont(160, L"Arial");
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
	rowHeights.push_back(rowHeight);
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

CTable& CTable::setRowHeight(int height,int row)
{
	if (row == -1) {
		row = rows - 1;
	}
	if (row >= 0 && height > 0) 
		rowHeights[row] = height; return *this;
}

CTable& CTable::draw(CDC* pDC)
{
	pDC->SelectObject(&font);
	CRect cellRect(0, 0, 0, 0);
	int rowHeightOffset = 0;
	int colOffset = offsetX;
	int rowOffset = offsetY + 2*headerHeight;
	for (int i = 0; i < rows; i++) {
		colOffset = offsetX;
		rowOffset = offsetY + 2 * headerHeight + rowHeightOffset;
		for (int j = 0; j < columns; j++) {
			cellRect.SetRect(colOffset, rowOffset, colOffset + columnWidths[j], rowOffset + rowHeights[i]);
			table[j][i]->draw(pDC, cellRect);
			if (columnWidths[j] < cellRect.Width())
			{
				columnWidths[j] = cellRect.Width();
			}
			if (rowHeights[i] < cellRect.Height())
			{
				rowHeights[i] = cellRect.Height();
			}
			colOffset += columnWidths[j];
		}
		rowHeightOffset += rowHeights[i];
	}

	int colWidth = 0;
	for (int i = 0; i < columns; i++) {
		colWidth += columnWidths[i];
	}
	CRect rect(offsetX, offsetY, offsetX + colWidth, offsetY + headerHeight);
	pDC->Rectangle(rect);
	pDC->DrawText(CString(name.c_str()), rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	colOffset = offsetX;
	rowOffset = offsetY+ headerHeight;
	pDC->MoveTo(colOffset, rowOffset);
	pDC->LineTo(colOffset, rowOffset + headerHeight);
	for (int i = 0; i < columns; i++) {
		CRect headerRect(colOffset, rowOffset, colOffset + columnWidths[i], rowOffset + headerHeight);
		pDC->MoveTo(colOffset, rowOffset + headerHeight);
		pDC->LineTo(colOffset + columnWidths[i], rowOffset + headerHeight);
		pDC->LineTo(colOffset + columnWidths[i], rowOffset);
		pDC->DrawText(CString(titles[i].c_str()), headerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		colOffset += columnWidths[i];
	}

	rowHeightOffset = 0;

	for (int i = 0; i < rows; i++) {
		colOffset = offsetX;
		rowOffset = offsetY + 2 * headerHeight + rowHeightOffset;
		pDC->MoveTo(colOffset, rowOffset);
		pDC->LineTo(colOffset, rowOffset + rowHeights[i]);
		for (int j = 0; j < columns; j++) {
			pDC->MoveTo(colOffset, rowOffset + rowHeights[i]);
			pDC->LineTo(colOffset + columnWidths[j], rowOffset + rowHeights[i]);
			pDC->LineTo(colOffset + columnWidths[j], rowOffset);
			CRect cellRect(colOffset, rowOffset, colOffset + columnWidths[j], rowOffset + rowHeights[i]);
			table[j][i]->draw(pDC, cellRect);
			colOffset += columnWidths[j];
		}
		rowHeightOffset += rowHeights[i];
	}
	return *this;
}

void IntCell::draw(CDC* pDC, CRect& rect)
{
	CString str;
	str.Format(L"%d", value);
	CSize textSize = pDC->GetTextExtent(str);
	if (textSize.cx > rect.Width()-30) {
		rect.right = rect.left + textSize.cx+30;
	}
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}


void DoubleCell::draw(CDC* pDC, CRect& rect)
{
	CString str;
	str.Format(L"%0.2f", value);
	CSize textSize = pDC->GetTextExtent(str);
	if (textSize.cx > rect.Width() - 30) {
		rect.right = rect.left + textSize.cx + 30;
	}
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

int getMaxWordWidth(CDC* pDC, CString cstr) {
	CString word;
	CSize wordSize;
	int maxWidth = 0;
	for (int i = 0; i <= cstr.GetLength(); ++i) {
		if (i == cstr.GetLength() || cstr[i] == ' ') {
			if (!word.IsEmpty()) {
				wordSize = pDC->GetTextExtent(word);
				if (wordSize.cx > maxWidth) {
					maxWidth = wordSize.cx;
				}
				word.Empty();
			}
		}
		else {
			word += cstr[i];
		}
	}
	return maxWidth;
}

int drawWords(CDC* pDC, CString cstr, int availableWidth,int x,int y) {
	CString word;
	CSize wordSize;
	int numLines = 0;
	CString currentLine;
	for (int i = 0; i <= cstr.GetLength(); ++i) {
		if (i == cstr.GetLength() || cstr[i] == ' ') {
			if (!word.IsEmpty()) {
				wordSize = pDC->GetTextExtent(word);
				if (pDC->GetTextExtent(currentLine + word).cx > availableWidth) {
					if (!currentLine.IsEmpty()) {
						pDC->TextOut(x, y, currentLine);
						y += wordSize.cy+5;
						numLines++;
						currentLine.Empty();
					}
				}
				if (!currentLine.IsEmpty()) {
					currentLine += _T(" ");
				}
				currentLine += word;

				word.Empty();
			}
		}
		else {
			word += cstr[i];
		}
	}
	if (!currentLine.IsEmpty()) {
		pDC->TextOut(x, y, currentLine);
		y += wordSize.cy+5;
		numLines++;
	}
	return numLines;
}

void StringCell::draw(CDC* pDC, CRect& rect)
{
	CString cstr(value.c_str());
	CSize textSize = pDC->GetTextExtent(cstr);
	if (textSize.cx > rect.Width() - 30) {
		int offset = 10;
		int padding = 15;

		int lineHeight = pDC->GetTextExtent(_T("A")).cy + 5;
		int availableWidth = rect.Width() - 2 * padding;
		int maxWidth = getMaxWordWidth(pDC, cstr);
		if (maxWidth > availableWidth) {
			availableWidth = maxWidth;
			rect.right = rect.left + maxWidth + 2 * padding;
		}

		int x = rect.left + padding;
		int y = rect.top + offset;

		int numLines = drawWords(pDC, cstr, availableWidth, x, y);
		rect.bottom = rect.top + numLines * lineHeight + offset;
	}
	else {
		pDC->DrawText(cstr, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}


void ImgCell::draw(CDC* pDC, CRect& rect)
{
	CImage img;
	HRESULT hr = img.Load(CString(path.c_str()));

	if (FAILED(hr)) {

		std::wstring wPath(path.begin(), path.end());
		CString errorMsg;
		errorMsg.Format(L"Image load failed: %s", wPath.c_str());
		CSize textSize = pDC->GetTextExtent(errorMsg);
		if (textSize.cx > rect.Width() - 30) {
			int offset = 10;
			int padding = 15;

			int lineHeight = pDC->GetTextExtent(_T("A")).cy + 5;
			int availableWidth = rect.Width() - 2 * padding;
			int maxWidth = getMaxWordWidth(pDC, errorMsg);
			if (maxWidth > availableWidth) {
				availableWidth = maxWidth;
				rect.right = rect.left + maxWidth + 2 * padding;
			}

			int x = rect.left + padding;
			int y = rect.top + offset;

			int numLines = drawWords(pDC, errorMsg, availableWidth, x, y);
			rect.bottom = rect.top + numLines * lineHeight + offset;
		}
		else
		{
			rect.left += 10;
			pDC->DrawText(errorMsg, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
		return;
	}
	CRect myRect(0,0,0,0);
	myRect.left = rect.left;
	myRect.top = rect.top;
	if (img.GetHeight() < rect.Height()) {
		myRect.top+= (rect.Height() - img.GetHeight()) / 2;
		myRect.bottom = myRect.top + img.GetHeight();
	}
	else {
		//AfxMessageBox(_T("Image height is bigger than cell height"));
		rect.bottom = img.GetHeight() + rect.top;	
		myRect.bottom = rect.bottom;
	}
	if (img.GetWidth() < rect.Width()) {
		//AfxMessageBox(_T("Image width is smaller than cell width"));
		myRect.left += (rect.Width() - img.GetWidth()) / 2;
		myRect.right = myRect.left + img.GetWidth();
	}
	else {
		rect.right = img.GetWidth() + rect.left;
		myRect.right = rect.right;
	}
	img.Draw(pDC->m_hDC, myRect);

}

CTable& CTable::addRow(const std::vector<void*>& values) {
	if (values.size() != columns) {
		throw std::invalid_argument("Values count should be equal to columns count" + std::to_string(columns) + " but was " + std::to_string(values.size()));
	}

	rows++;

	for (int i = 0; i < columns; i++) {
		if (table[i].size() <= rows) {
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

	rowHeights.push_back(rowHeight);

	// «аписываем значени€ в €чейки дл€ текущей строки
	for (int i = 0; i < columns; i++) {
		if (table[i][rows - 1] == nullptr) {
			throw std::runtime_error("Cell is nullptr at row " + std::to_string(rows) + " and column " + std::to_string(i));
		}

		// ”станавливаем значение в €чейку
		table[i][rows - 1]->setValue(values[i],this);
	}

	return *this;
}

int CTable::getHeight() const
{
	int height = 2 * offsetY + headerHeight * 2;
	for (int i = 0; i < rows; i++) {
		height += rowHeights[i];
	}
	return height;
}

int CTable::getWidht() const
{
	int width = 2 * offsetX;
	for (int i = 0; i < columns; i++) {
		width += columnWidths[i];
	}
	return width;
}