class Shop {

	bool _active = false;
public:
	Shop() {}
	~Shop() = default;

	void init();
	void render();
	void click(Vector2 position);

	bool isActive() { return _active; }
};