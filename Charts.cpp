#include <vector>
#include <string>
#include <functional>

template <class Element>
class Collection
{
	public:
	virtual Collection <Element>* collectionWithNewElement (Element*) = 0;
};

template <class Collection, class Element, class Update>
class Iterator
{
	public:
	virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Element* current() = 0;
	virtual void updateCurrentToNewCollection (Update*) = 0;
	virtual Iterator <Collection, Element, Update>* updatedCollectionIterator() = 0;
};

template <class Iterator, class Function>
void forEach (Iterator* iterator, Function function)
{
	for (iterator.first(); !iterator.isDone(); iterator.next()) {
		function (iterator);
	}
}

class ChartPoint
{
	public:
	virtual std::string* valueName() = 0;
	virtual double numberValue() = 0;
	virtual App* app() = 0;
};

class ChartPointsIterator
{
	public:
	virtual Iterator <Collection <ChartPoint>, ChartPoint, Event> generalizedIterator() = 0;
	virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual ChartPoint* current() = 0;
	virtual void updateCurrentChartPointsToNewChartPoints (Event*) = 0;
	virtual ChartPointsIterator* updatedChartPointsIterator() = 0;
};

class Chart
{
	public:
	virtual Chart* updatedChart (Event*) = 0;
	virtual std::string* name() = 0;
	virtual ChartPointsIterator* chartPointsIterator() = 0;
};

class ScreenTimeAllAppsMounth : public Chart
{
	public:
	ScreenTimeAllAppsMounth (std::string* name, Collection <ChartPoint>* chartPoints)
	: _name {name}, _chartPoints {chartPoints}
	{
	}

	ScreenTimeAllAppsMounth* updatedChart (Event* event) override
	{
		forEach (_chartPointsIterator,
		         [event] (ChartPointsIterator* chartPointsIterator) {chartPointsIterator->updateCurrentChartPointsToNewChartPoints(event);}
		);
		return new ScreenTimeAllAppsMounth (_name, _chartPointsIterator);
	}

	std::string* name() override
	{
		return _name;
	}

	ChartPointsIterator* chartPointsIterator() override
	{
		return _chartPointsIterator;
	}

	private:
	std::string* _name;
	Collection <ChartPoint>* _chartPoints;
	ChartPointsIterator* _chartPointsIterator;
};

class ChartsIterator
{
	public:
	virtual Iterator <Collection <Chart>, Chart, Event> generalizedIterator() = 0;
	virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Chart* current() = 0;
	virtual void updateCurrentChartsToNewCharts (Event*) = 0;
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
			forEach (_chartsIterator,
			         [event] (ChartsIterator* chartsIterator) {chartsIterator->updateCurrentChartsToNewCharts (event);}
			);
			ChartsIterator* updatedChartsIterator = _chartsIterator->updatedChartsIterator();
			forEach (updatedChartsIterator,
			         [_thisAppWindow] (ChartsIterator* updatedChartsIterator) {_thisAppWindow->print (updatedChartsIterator->current());}
			);
		}
	}

	private:
	UserPC* _userPC;
	ChartsIterator* _chartsIterator;
	ThisAppWindow* _thisAppWindow;
};