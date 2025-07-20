#ifndef AUTOCLICK_H
#define AUTOCLICK_H

#include <QWidget>

class autoClick : public QWidget
{
    Q_OBJECT

public:
	autoClick(QWidget* parent)
		: QWidget(parent)
	{
	}

	~autoClick() = default;
};
#endif // AUTOCLICK_H
