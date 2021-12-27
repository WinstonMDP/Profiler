#include <vector>
#include <string>
#include <functional>

template <class Element, class Update>
class Collection
{
	public:
	virtual Iterator <Collection <Element, Update>, Element, Update> iterator() = 0;
};

template <class Element, class Update>
class VectorCollection : public Collection <Element, Update>
{
	public:
	Iterator <Collection <Element, Update>, Element, Update> iterator()
	{
		return new VectorIterator (_vector);
	}

	private:
	std::vector <Element>* _vector;
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

template <class Element, class Update>
class VectorIterator : public Iterator <Collection <Element, Update>, Element, Update>
{
	public:
	VectorIterator (std::vector <Element>* vector)
	: _vector {vector}
	{
	}

	void first() override
	{
		if (isUpdated) {
			throw "It collection has already updated. We use immutable way.";
		}

		if (_vector->size() > 0) {
			_currentIndex = 0;
		}
		else {
			throw "It doesn`t have elements.";
		}
	}

	bool isDone() override
	{
		return _currentIndex == _vector->size();
	}

	void next() override
	{
		++_currentIndex;
		if (_currentIndex > _vector->size()) {
			throw "_CurrentIndex > vector.size()";
		}
	}

	Element* current() override
	{
		return _vector.at (_currentIndex);
	}

	void updateCurrentToNewCollection (Update* update) override
	{
		_vector->at (_currentIndex)->update (update);
		_isUpdated = true;
	}

	Iterator <Collection <Element, Update>, Element, Update>* updatedCollecitonIterator()
	{
		return new VectorIterator (_vector);
	}

	private:
	std::vector <Element>* _vector;
	long _currentIndex;
	bool _isUpdated = false;
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
	virtual void update() = 0;
};

class ChartPointsIterator : public Iterator <Collection <ChartPoint, Event>, ChartPoint, Event>
{
	public:
	virtual void updateCurrentChartPointToNewChartPoints (Event*) = 0;
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
	ScreenTimeAllAppsMounth (std::string* name, Collection <ChartPoint, Event>* chartPoints)
	: _name {name}, _chartPoints {chartPoints}, _chartPointsIterator {new ChartPointsIterator (chartPoints)}
	{
	}

	ScreenTimeAllAppsMounth* updatedChart (Event* event) override
	{
		forEach (_chartPointsIterator,
		        [event] (ChartPointsIterator* chartPointsIterator)
				{chartPointsIterator->updateCurrentChartPointToNewChartPoints (event);}
		);
		ChartPointsIterator* updatedChartPointsIterator = _chartPointsIterator->updatedChartPointsIterator();
		return new ScreenTimeAllAppsMounth (_name, updatedChartPointsIterator);
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
	Collection <ChartPoint, Event>* _chartPoints;
	ChartPointsIterator* _chartPointsIterator;
};

class ChartsIterator : public Iterator <Collection <Chart, Event>, Chart, Event>
{
	public:
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
			        [event] (ChartsIterator* chartsIterator)
					{chartsIterator->updateCurrentChartsToNewCharts (event);}
			);
			ChartsIterator* updatedChartsIterator = _chartsIterator->updatedChartsIterator();
			forEach (updatedChartsIterator,
			        [_thisAppWindow] (ChartsIterator* updatedChartsIterator)
					{_thisAppWindow->print (updatedChartsIterator->current());}
			);
		}
	}

	private:
	UserPC* _userPC;
	ChartsIterator* _chartsIterator;
	ThisAppWindow* _thisAppWindow;
};