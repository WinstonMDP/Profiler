#include <string>

class Chart
{
	public:
	virtual Chart* updatedChart (Event*) = 0;
};

template <class Element>
class Collection
{
	public:
	virtual Collection <Element>* collectionWithNewElement (Element*) = 0;
};

class ChartsIterator
{
	public:
	virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Chart* current() = 0;
	virtual void updateCurrentInNewCharts (Event*) = 0;
	virtual ChartsIterator* updatedChartsIterator() = 0;
};

class ThisAppWindow
{
	public:
	virtual void print (Chart*) = 0;
};

class TimeType
{
	public:
	virtual std::string* string() = 0;
};

class Data
{
	public:
	virtual long seconds() = 0;
	virtual long minutes() = 0;
	virtual long hours() = 0;
	virtual long days() = 0;
	virtual long months() = 0;
	virtual long years() = 0;
};

class Image
{
};

class App
{
	public:
	virtual std::string* name() = 0;
	virtual Image* icon() = 0;
};

class Event
{
	public:
	virtual TimeType* timeType() = 0;
	virtual Data* data() = 0;
	virtual App* app() = 0;
};

class UserPC
{
	public:
	virtual Event* event() = 0;
};

class Main
{
	public:
	void startUpdatingAndPrintingLoop()
	{
		while (true) {
			Event* event = _userPC->event();
			for (_chartsIterator->first() ; !_chartsIterator->isDone(); _chartsIterator->next()) {
				_chartsIterator->updateCurrentInNewCharts (event);
			}
			ChartsIterator* updatedChartsIterator = _chartsIterator->updatedChartsIterator();
			for (updatedChartsIterator->first(); !updatedChartsIterator->isDone(); updatedChartsIterator->next()) {
				_thisAppWindow->print (updatedChartsIterator->current());
			}
		}
	}

	private:
	UserPC* _userPC;
	ChartsIterator* _chartsIterator;
	ThisAppWindow* _thisAppWindow;
};