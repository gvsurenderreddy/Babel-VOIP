#ifndef QTNETWORK_TESTS_H
#define QTNETWORK_TESTS_H

#include <QtWidgets/QMainWindow>
#include "ui_qtnetwork_tests.h"
#include "IClientSocket.hpp"
#include "IServerSocket.hpp"

class qtnetwork_tests : public QMainWindow, public IClientSocket::OnSocketEvent, public IServerSocket::OnSocketEvent
{
	Q_OBJECT

public:
	qtnetwork_tests(QWidget *parent = 0);
	~qtnetwork_tests();

private:
	Ui::qtnetwork_testsClass ui;

public:
	void	onSocketReadyRead(IClientSocket *socket);
	void	onSocketClosed(IClientSocket *socket);
	void	onNewConnection(IServerSocket *socket);

private:
	IClientSocket *client;
	IServerSocket *server;
};

#endif // QTNETWORK_TESTS_H
