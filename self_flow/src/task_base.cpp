class TaskNode //make into an action server
{
private:
  double base_utility;


public:
  TaskNode(double ut)
  {
	base_utility=ut;
  }

  virtual void execute();

  virtual double utility(double w1, double w2, double w3, double w4)
  {
	return 0.0;
  }
}

