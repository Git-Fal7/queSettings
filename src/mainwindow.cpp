#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QDirIterator>
#include <list>

QStringList DesktopList;

MainWindow::MainWindow(QWidget *parent) :    QMainWindow(parent),     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();

    /*for (int i=0; i<30; i++){
		QTreeWidgetItem *lastIt = new QTreeWidgetItem();
		lastIt->setText(0, "Hello !");
		ui->treeWidget->addTopLevelItem(lastIt);			
	}
	ui->treeWidget->sortItems(0, Qt::AscendingOrder);
	ui->treeWidget->resizeColumnToContents(0);
	ui->treeWidget->resizeColumnToContents(1);*/
	
	connect(ui->treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(itemTriggered(QTreeWidgetItem*, int)) );
    connect(ui->treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(itemTriggered(QTreeWidgetItem*, int)) );
	
}

QStringList MainWindow::readFile(QString filepath){
  QStringList out;
  QFile file(filepath);
  if(file.open(QIODevice::Text | QIODevice::ReadOnly)){
    QTextStream in(&file);
    while(!in.atEnd()){
      out << in.readLine();
    }
    file.close();
  }
  return out;
}

void MainWindow::loadSettings(){
	QDir dir("/usr/share/applications");
	QDirIterator iterator(dir.absolutePath(), QDirIterator::Subdirectories);
	QStringList paths;
	
	while(iterator.hasNext()){
		QFile file(iterator.next());
		if (file.open(QIODevice::ReadOnly)) {
			if (file.fileName().toLower().endsWith(".desktop")){
				//qDebug() << "opend:" << file.fileName() << Qt::endl;

				QStringList dfile = readFile(file.fileName());
				for(int i=0; i<dfile.length(); i++){
					QString line = dfile[i];
					if (line.contains("Categories=")){
						if (line.toLower().contains("settings")){
							//qDebug() << line;
							paths << file.fileName();
						}
					}
				}
			}
		}
	}
	for(int i = 0; i < paths.length(); i++){
		//qDebug() << paths[i];
		QString name;
		QString icon;
		QString exec;
		QString desc;
		QStringList dfile = readFile(paths[i]);
		for(int i=0; i<dfile.length(); i++){
			QString line = dfile[i];
			if (line.startsWith("Name=")) {
				line = line.replace("Name=", "");
				name = line;
			}
			if (line.startsWith("Exec=")) {
				line = line.replace("Exec=", "").remove("%U").remove("%u").remove("%F").remove("%f").remove("%i").remove("%c").remove("%k").simplified();
				exec = line;
			}
			if (line.startsWith("Icon=")) {
				line = line.replace("Icon=", "");
				icon = line;
			}
			if (line.startsWith("Comment=")) {
				line = line.replace("Comment=", "");
				desc = line;
			}

		}
		//QStringList li = (QStringList() << name << exec << icon);
		QString li = name + "<>" + exec + "<>" + icon + "<>" + desc;
		DesktopList << li;
	}
	qDebug() << DesktopList;
	loadItems();
}


void MainWindow::loadItems(){
	ui->treeWidget->clear();
	ui->treeWidget->setColumnCount(2);
	
	for (int i=0; i<DesktopList.length(); i++){
		QStringList li = DesktopList[i].split("<>");
		QTreeWidgetItem *lastIt = new QTreeWidgetItem();
		QIcon icon = QIcon::fromTheme(li[2]);
		lastIt->setIcon(0, icon);
		lastIt->setText(0, li[0]);
		lastIt->setWhatsThis(0, li[1]);
		lastIt->setToolTip(0, li[3]);
		ui->treeWidget->addTopLevelItem(lastIt);			
	}
	
	ui->treeWidget->sortItems(0, Qt::AscendingOrder);
	ui->treeWidget->resizeColumnToContents(0);
	ui->treeWidget->resizeColumnToContents(1);
	
}

//This executes when an item is clicked
void MainWindow::itemTriggered(QTreeWidgetItem *it, int col){
	if(it->childCount()>0) {
		it->setExpanded( !it->isExpanded() );
		it->setSelected(false);
	}else if(!it->whatsThis(col).isEmpty()) {
		QString id = it->whatsThis(col);
		if(!id.isEmpty()) {
			QProcess::startDetached(id);
		}
	} else {
		it->setSelected(false);
	}
}


MainWindow::~MainWindow()
{
    delete ui;
}
