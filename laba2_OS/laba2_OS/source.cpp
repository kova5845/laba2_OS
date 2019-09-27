class Point 
{
	double x, y;
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
};

double Point :: getX() 
{
	return x;
}

double Point :: getY() 
{
	return y;
}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}


