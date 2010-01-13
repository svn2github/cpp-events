/**************************************************************/
/* Goal of this test is to check if it is possible to declare */
/* new inner type inside function declaration                 */
/*                                                            */
/* InnerTestClass is prototype for future event-ref class     */
/**************************************************************/

class OuterTestClass
{
public:
	class InnerTestClass
	{
	public:
		InnerTestClass(OuterTestClass * inst) : inst_(inst) {}
		int value() const { return inst_->x_; }
		void setValue(int v) { inst_->x_ = v; }
	private:
		OuterTestClass * inst_;
	} propertyX() { return this; }
private:
	int x_;
};

void main()
{
	OuterTestClass c;
	int q = c.propertyX().value();
	c.propertyX().setValue(q + 24);
}