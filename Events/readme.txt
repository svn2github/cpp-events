
1) Events
  1) declaring event implementation:
		Event<double,int,QString> clicked_;
  2) event invokation:
		clicked_(2.3, -1, tr("Hello, World!"));
  3) declaring connection interface:
		EventRef<double,int,QString> clicked() { return clicked_.bind(this); }
		EventRef<double,int,QString> clicked() { return innerObject_->clicked().rebind(this); }
  4) declaring connection storage:
		Connector connector_;
  5) connecting:
		connector_.connect(sender->clicked(), this, &MyClass:handlerName, data1, data2, ... dataN);
		connector_.disconnectAll();
		connector_.disconnectSender(sender);
		connector_.disconnectReciever(this);
		connector_.disconnect(sender, this);
		connector_.disconnect(sender->clicked());
		connector_.disconnect(this, &MyClass:handlerName);
		connector_.disconnect(sender->clicked(), this, &MyClass:handlerName);
		
Фичи, которые еще надо реализовать:
  ConnectionList/Map (QPtr)
  ConnectionEx1
 		
