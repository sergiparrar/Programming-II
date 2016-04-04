class Foo
{
public:
	int n;
	Foo() : n(0){};
	int get(){ return n; }
	int getc() const { return n; }
}

int main()
{
	const Foo bar;
	Foo baz;
	int n1 = baz.get();
	int n2 = bar.getc();
}