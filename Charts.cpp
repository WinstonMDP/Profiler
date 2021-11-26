#include <string>

class Chart
{
	public:
	virtual Chart updatedChart (Event) = 0;
};

template <class Element>
class Collection
{
	public:
	virtual Collection <Element> collectionWithNewElement (Element) = 0;
	virtual Iterator iterator () = 0;
};

class ThisAppWindow
{
	public:
	virtual void print (Chart) = 0;
};

class TimeType
{
	public:
	virtual std::string string() = 0;
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
	virtual std::string name() = 0;
	virtual Image icon() = 0;
};

class Event
{
	public:
	virtual TimeType timeType() = 0;
	virtual Data data() = 0;
	virtual App app() = 0;
};

class UserPC
{
	public:
	virtual Event event() = 0;
};

class Main
{
	public:
	void startUpdatingAndPrintingLoop()
	{

		while (true) {
			for (_chartsIterator->first() ; !_chartsIterator->isDone(); _chartsIterator->next()) {
			}
		}
	}

	private:
	Iterator* _chartsIterator;
};