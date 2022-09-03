#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<iomanip>
using namespace std;

bool errorcheck = false;
template<typename t>
void extend(t*& arr, int size)
{
	if (size > 0)
	{
		t* temp = new t[size];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = new t[size + 1];
		for (int i = 0; i < size; i++)
		{
			arr[i] = temp[i];
		}
	}
	else
	{
		arr = new t[size + 1];
	}
}


template<typename t>
void remove(t*& arr, int& size, int index)
{
	if (size > 0 && index >= 0)
	{
		t* temp = new t[size];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = new t[size - 1];
		for (int i = 0; i < index; i++)
		{
			arr[i] = temp[i];
		}
		for (int i = index; i < size - 1; i++)
		{
			arr[i] = temp[i + 1];
		}
	}
	size--;
}

template<typename t>
void readcustdatafromfile(t*& arr, int& size)
{
	string name, address, phone, email;
	int id;
	ifstream fin("customers.txt");
	for (int i = 0; !fin.eof(); i++)
	{
		fin >> id;

		fin.ignore();

		getline(fin, name);

		getline(fin, address);

		getline(fin, phone);

		getline(fin, email);

		extend(arr, size);
		arr[size].entry(id, name, address, phone, email);
		size++;
	}
	fin.close();
}

template<typename t>
void readtrainerdatafromfile(t*& arr, int& size)
{
	string name;
	int id;
	ifstream fin("trainers.txt");
	for (int i = 0; !fin.eof(); i++)
	{
		extend(arr, size);
		fin >> id;
		fin.ignore();
		getline(fin, name);
		arr[size].entry(id, name);
		size++;
	}
	fin.close();
}

template<typename t>
void readeqdatafromfile(t*& arr, int& size)
{
	string name;
	int id;
	ifstream fin("equipments.txt");
	for (int i = 0; !fin.eof(); i++)
	{
		extend(arr, size);
		fin >> id;
		fin.ignore();
		getline(fin, name);
		arr[size].entry(id, name);
		size++;
	}
	fin.close();
}

template<typename t>
void readepdatafromfile(t*& arr, int& size)
{
	int _planid;
	int _trainid;
	int _eqid;
	int _duration;
	ifstream fin("excercisePlans.txt");
	for (int i = 0; !fin.eof(); i++)
	{
		extend(arr, size);
		fin >> _planid;
		fin >> _trainid;
		fin >> _eqid;
		fin >> _duration;
		arr[size].entry(_planid, _trainid, _eqid, _duration);
		size++;
	}
	fin.close();
}

template<typename t>
void readsubdatafromfile(t*& arr, int& size)
{
	string temp;
	ifstream fin("subscriptions.txt");
	for (int i = 0; !fin.eof(); i++)
	{
		extend(arr, size);
		fin >> arr[i].id;
		fin >> temp;
		arr[i].subdate.entry(temp);
		fin >> arr[i].custid;
		fin >> arr[i].planid;
		size++;
	}
	fin.close();
}

template <typename t>
int findid(t*& arr, int size, int id)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i].id == id)
		{
			return i;
		}
	}
	return -1;
}

void menu()
{
	
	cout << "|**********************************MENU*****************************************|\n";
	cout << "| 1)Add , Edit or Delete the Object.                                            |\n";
	cout << "| 2)Check Availability of Trainer or Equipments                                 |\n";
	cout << "| 3)Enquire about customer’s Inquiry                                            |\n";
	cout << "| 4)Save the data and Exit Option.                                              |\n";
	cout << "| 5)Print All The Data For Testing Purposes Only.                               |\n";
	cout << "|*******************************************************************************|\n";
	cout << endl;
}

template<typename t>
bool checkavail(t*& obj, int length, int id)
{
	for (int i = 0; i < length; i++)
	{
		if (obj[i].getid() == id) {
			return false;
		}
	}
	return true;
}

class customer {
	string custname;
	int id;
	string custaddress;
	string custphone;
	string custemail;
public:
	customer()
	{
		id = 0;
	}
	customer(int _id, string name, string address, string phone, string email)
	{
		id = _id;
		custname = name;
		custaddress = address;
		custphone = phone;
		custemail = email;
	}
	void entry(int _id, string name, string address, string phone, string email)
	{
		id = _id;
		custname = name;
		custemail = email;
		custaddress = address;
		custphone = phone;
	}
	void modifydata()
	{

		int ch;
		cout << "0) ID \n1) Name \n2) Address\n3) Phone Number\n4) Email\nChoice : ";
		cin >> ch;
		switch (ch)
		{
		case 0:
			cout << "Kindly Enter the NEW ID :";
			cin >> id;
			break;
		case 1:
			cin.ignore();
			cout << "Kindly Enter the NEW Name :";
			getline(cin, custname);
			break;
		case 2:
			cin.ignore();
			cout << "Kindly Enter the NEW Address :";
			getline(cin, custaddress);
			break;
		case 3:
			cin.ignore();
			cout << "Kindly Enter the NEW  Phone Number :";
			getline(cin, custphone);
			break;
		case 4:
			cin.ignore();
			cout << "Kindly Enter the NEW Email :";
			getline(cin, custemail);
			break;
		}

	}

	void print()
	{
		cout << "Customer ID: " << id << endl;
		cout << "Customer name: " << custname << endl;
		cout << "Customer address: " << custaddress << endl;
		cout << "Customer phone: " << custphone << endl;
		cout << "Customer email:" << custemail << endl;
		cout << endl;
	}
	template<typename t>
	friend 	void readcustdatafromfile(t*& arr, int& size);

	void setcustname(string c) {
		custname = c;
	}
	string getcustname() {
		return custname;
	}

	void setid(int i) {
		id = i;
	}
	int getid() {
		return id;
	}

	void setcustaddress(string a) {
		custaddress = a;
	}
	string getcustaddress() {
		return custaddress;
	}

	void setcustemail(string e) {
		custemail = e;
	}
	string getcustemail() {
		return custemail;
	}
	void setcustphone(string p) {
		custphone = p;
	}
	string getcustphone() {
		return custphone;
	}
	template <typename t>
	friend int findid(t*& arr, int size, int id);

};

class trainer {
	int id;
	string tranname;
public:

	trainer()
	{
		id = 0;
	}
	trainer(int _id, string name)
	{
		id = _id;
		tranname = name;
	}
	void entry(int _id, string name) {
		id = _id;
		tranname = name;
	}
	void modifydata()
	{
		int  ch;
		cout << "0) ID \n1) Name \nChoice : ";
		cin >> ch;
		switch (ch)
		{
		case 0:
			cout << "Kindly Enter the NEW  ID :";
			cin >> id;
			break;
		case 1:
			cin.ignore();
			cout << "Kindly Enter the NEW  Name :";
			getline(cin, tranname);
			break;
		}
	}
	void settrainerid(int i) {
		id = i;
	}
	int gettainerid() {
		return id;
	}
	int getid() {
		return id;
	}
	void settranname(string tn) {
		tranname = tn;
	}
	string gettranname() {
		return tranname;
	}

	void print()
	{
		cout << "Trainer ID:" << id << endl;
		cout << "Trainer Name:" << tranname << endl;
		cout << endl;
	}
	template<typename t>
	friend 	void readtrainerdatafromfile(t*& arr, int& size);
	template <typename t>
	friend int findid(t*& arr, int size, int id);
};

class equipment {
	int id;
	string eqname;
public:
	equipment()
	{
		id = 0;
	}
	equipment(int _id, string name)
	{
		id = _id;
		eqname = name;
	}
	void entry(int _id, string name)
	{
		id = _id;
		eqname = name;
	}

	void modifydata()
	{
		int index, id_user, ch;
		cout << "0) ID\n 1) Name \nChoice : ";
		cin >> ch;
		switch (ch)
		{
		case 0:
			cout << "Kindly Enter the NEW  ID :";
			cin >> id;
			break;
		case 1:
			cin.ignore();
			cout << "Kindly Enter the NEW  Name :";
			getline(cin, eqname);
			break;
		}
	}

	void print()
	{
		cout << "Equipment ID: " << id << endl;
		cout << "Equipment name: " << eqname << endl;
		cout << endl;
	}

	template<typename t>
	friend 	void readeqdatafromfile(t*& arr, int& size);
	void seteqid(int e) {
		id = e;
	}
	int getid() {
		return id;
	}
	void seteqname(int e) {
		eqname = e;
	}
	string geteqname() {
		return eqname;
	}
	template <typename t>
	friend int findid(t*& arr, int size, int id);
};

class exerciseplan
{
	int id;
	trainer* trainid = nullptr;
	equipment* eqid = nullptr;
	int duration;
public:
	void init()
	{
		trainid = new trainer;
		eqid = new equipment;
	}
	void entry(int _id, int _trainid, int _eqid, int _duration)
	{
		init();
		id = _id;
		trainid[0].settrainerid(_trainid);
		eqid[0].seteqid(_eqid);
		duration = _duration;
	}
	void print()
	{
		cout << "customer id : " << id << endl;
		cout << "trainer id : " << trainid[0].gettainerid() << endl;
		cout << "equipment id : " << eqid[0].getid() << endl;
		cout << "Duration : " << duration <<" mins" << endl;
		cout << endl;
	}
	template<typename t>
	friend 	void readepdatafromfile(t*& arr, int& size);
	void modifydata()
	{
		int ch, trid, eqids;
		cout << "0)Plan ID \n1)Trainer ID \n2)Equipment ID \n3)Duration \nChoice : ";
		cin >> ch;
		switch (ch)
		{
		case 0:
			cout << "Kindly Enter the NEW  Plan ID :";
			cin >> id;
			break;
		case 1:
			cout << "Kindly Enter the NEW Trainer ID :";
			cin >> trid;
			trainid[0].settrainerid(trid);
			break;
		case 2:
			cout << "Kindly Enter the NEW Equipment ID :";
			cin >> eqids;
			eqid[0].seteqid(eqids);
			break;
		case 3:
			cout << "Kindly Enter the NEW  Duration :";
			cin >> duration;
			break;
		default:
			cout << "Wrong Choice. ";
			break;
		}
	}
	void setid(int i) {
		id = i;
	}
	int getid() {
		return id;
	}
	void settrainid(int t) {
		trainid[0].settrainerid(t);
	}
	int gettrainid() {
		return trainid[0].gettainerid();
	}
	void seteqid(int eq) {
		eqid[0].seteqid(eq);
	}
	int geteqid() {
		return eqid[0].getid();
	}
	void setduration(int d) {
		duration = d;
	}
	int getduration() {
		return duration;
	}
	template <typename t>
	friend int findid(t*& arr, int size, int id);
};

class date {
	string dates;
	int day, month, year;
public:
	date()
	{

	}
	date(string _date)
	{
		dates = _date;
	}
	void datacorrect()   ///26/26/2022....... 1/12/2022....... 1/1/2022...... 10/1/2022
	{
		if (errorcheck)
		{
			if (dates.size() == 10)
			{
				day = ((dates[0] - 48) * 10) + (dates[1] - 48);
				if (dates[2] != 47)
				{

					cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
					cin >> dates;
				}
				month = ((dates[3] - 48) * 10) + (dates[4] - 48);
				if (dates[5] != 47)
				{
					cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
					cin >> dates;
				}
				year = ((dates[6] - 48) * 1000) + ((dates[7] - 48) * 100) + ((dates[8] - 48) * 10) + (dates[9] - 48);
			}
			else if (dates.size() == 9)
			{
				if ((dates[0] > 48 && dates[0] < 58) && (dates[1] > 48 && dates[1] < 58))
				{
					day = ((dates[0] - 48) * 10) + (dates[1] - 48);
					if (dates[2] == 47)
					{
						cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
						cin >> dates;
					}
					else
					{
						if ((dates[3] > 48 && dates[3] < 58) && (dates[4] > 48 && dates[4] < 58))
						{
							month = ((dates[3] - 48) * 10) + (dates[4] - 48);
						}
						else if ((dates[3] > 48 && dates[3] < 58) && dates[4] == 57)
						{
							month = (dates[3] - 48);
							year = ((dates[5] - 48) * 1000) + ((dates[6] - 48) * 100) + ((dates[7] - 48) * 10) + (dates[8] - 48);
						}
						else
						{
							cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
							cin >> dates;
						}
					}
				}
				else if ((dates[0] > 48 && dates[0] < 58) && dates[1] == 47)
				{
					day = (dates[0] - 48);
					if ((dates[2] > 48 && dates[2] < 58) && (dates[3] > 48 && dates[3] < 58))
					{
						month = ((dates[2] - 48) * 10) + (dates[3] - 48);
					}
					else if ((dates[2] > 48 && dates[2] < 58) && dates[3] == 47)
					{
						month = (dates[2] - 48);

						year = ((dates[4] - 48) * 1000) + ((dates[5] - 48) * 100) + ((dates[6] - 48) * 10) + (dates[7] - 48);
					}
					else
					{
						cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
						cin >> dates;
					}

				}
				else
				{
					cout << "Incorrect Date Found Kindly Re-Renter format dd/mm/yyyy : ";
					cin >> dates;
				}
				month = ((dates[3] - 48) * 10) + (dates[4] - 48);
				year = ((dates[6] - 48) * 1000) + ((dates[7] - 48) * 100) + ((dates[8] - 48) * 10) + (dates[9] - 48);
			}
			else if (dates.size() == 8)
			{
				if ((dates[0] > 48 && dates[0] < 58) && dates[1] == 47)
				{
					if ((dates[2] > 48 && dates[2] < 58) && dates[3] == 47)
					{
						day = (dates[0] - 48);
						month = (dates[2] - 48);
						year = ((dates[4] - 48) * 1000) + ((dates[5] - 48) * 100) + ((dates[6] - 48) * 10) + (dates[7] - 48);
					}
					else
					{
						cout << "You have entered the wrong date. Kindly Re-enter Format dd/mm/yyyy : ";
						cin >> dates;
					}
				}
				else
				{
					cout << "You have entered the wrong date. Kindly Re-enter Format dd/mm/yyyy : ";
					cin >> dates;
				}
			}
			if (day > 31 || day < 1)
			{
				cout << "You have entered the wrong date. Kindly Re-enter Format dd/mm/yyyy : ";
				cin >> dates;
			}
			if (month > 12 || month < 1)
			{
				cout << "You have entered the wrong month. Kindly Re-enter Format dd/mm/yyyy  : ";
				cin >> dates;
			}
			if (year < 2000 || year > 2100)
			{
				cout << "you have entered the Year. Year should be Year>2000 && Year < 2100 .";
				cin >> dates;
			}
		}
	}

	void entry(string _date)
	{
		dates = _date;
		datacorrect();
	}

	void print()
	{
		cout << "Date: " << dates << endl;
	}

	string ret()
	{
		return dates;
	}
	friend class subscription;
};

class subscription {
	int id;
	date subdate;
	int custid;
	int planid;
public:
	subscription()
	{

	}
	subscription(int _id, int _custid, int _planid, date temp)
	{
		id = _id;
		custid = _custid;
		planid = _planid;
		subdate = temp;
	}
	void entry(int _id, int _custid, int _planid, date temp)
	{
		id = _id;
		custid = _custid;
		planid = _planid;
		subdate = temp;
	}
	void modifydata()
	{
		int ch;
		string temp;

		cout << "What do you want to modify ? \n0)Subscription ID \n1)Customer ID \n2)Plan ID \n3)Date\nChoice : ";
		cin >> ch;
		switch (ch)
		{
		case 0:
			cout << "Kindly Enter NEW  Subscription ID : ";
			cin >> id;
			break;
		case 1:
			cout << "Kindly Enter the NEW Customer ID : ";
			cin >> custid;
			break;
		case 2:
			cout << "Kindly Enter the NEW Plan ID : ";
			cin >> planid;
			break;
		case 3:
			cout << "Kindly Enter the Date  in Format like 11/02/2020: ";
			cin >> temp;
			subdate.entry(temp);
			break;
		default:
			cout << "You have entered the Wrong Option.";
		}

	}
	void print()
	{
		cout << "subscription id: " << id << endl;
		subdate.print();
		cout << "customer id: " << custid << endl;
		cout << "plan id: " << planid << endl;
		cout << endl;
	}
	template<typename t>
	friend 	void readsubdatafromfile(t*& arr, int& size);
	void setid(int s) {
		id = s;
	}
	int getid() {
		return id;
	}
	void setsubdate(date d) {
		subdate = d;
	}
	date getsubdate() {
		return subdate;
	}
	void setcustid(int c) {
		custid = c;
	}
	int getcustid() {
		return custid;
	}
	void setplanid(int p) {
		planid = p;
	}
	int getplanid() {
		return planid;
	}
	string datestr()
	{
		return subdate.ret();
	}
	template <typename t>
	friend int findid(t*& arr, int size, int id);
};

int retplanid(subscription*& obj, int length, int index)
{
	return obj[index].getid();
}
int checkplans(exerciseplan*& obj, int length, int trainid, int eqid)
{
	for (int i = 0; i < length; i++)
	{
		if (obj[i].gettrainid() == trainid && obj[i].geteqid() == eqid)
		{
			return i;
		}
	}
	return -1;
}
bool checkdate(subscription*& obj, int length, string tempdate)
{
	for (int i = 0; i < length; i++)
	{
		if (obj[i].datestr() == tempdate)
		{
			return false;
		}
	}
	return true;
}

class gym {
	customer* a;
	int custsize;
	trainer* b;
	int trainersize;
	equipment* c;
	int eqsize;
	exerciseplan* d;
	int epsize;
	subscription* e;
	int subsize;
public:
	void init()
	{
		a = nullptr;
		b = nullptr;
		c = nullptr;
		d = nullptr;
		e = nullptr;
		custsize = 0;
		trainersize = 0;
		epsize = 0;
		eqsize = 0;
		subsize = 0;
	}
	gym()
	{
		init();
	}
	gym(customer*& _a, trainer*& _b, equipment*& _c, exerciseplan*& _d, subscription*& _e, int _custsize, int _trainersize, int _eqsize, int _epsize, int _subsize)
	{
		init();
		a = _a;
		b = _b;
		c = _c;
		d = _d;
		e = _e;
		custsize = _custsize;
		trainersize = _trainersize;
		eqsize = _eqsize;
		epsize = _epsize;
		subsize = _subsize;
	}

	void printalldata()
	{
		cout << "\t\t\tCustomers " << endl;
		for (int i = 0; i < custsize; i++)
		{
			a[i].print();
		}
		cout << endl;

		cout << "\t\t\tTrainers " << endl;
		cout << endl << endl;
		for (int i = 0; i < trainersize; i++)
		{
			b[i].print();
		}
		cout << endl << endl;
		
		cout << "\t\t\tEquipments " << endl;
		for (int i = 0; i < eqsize; i++)
		{
			c[i].print();
		}
		cout << endl << endl;
		
		cout << "\t\t\tExercise Plans " << endl;
		for (int i = 0; i < epsize; i++)
		{
			d[i].print();
		}
		cout << endl;
		
		cout << "\t\t\tSubscriptions " << endl;
		for (int i = 0; i < subsize; i++)
		{
			e[i].print();
		}
		cout << endl;
	}

	void printcust()
	{
		cout << "Customers " << endl;
		for (int i = 0; i < custsize; i++)
		{
			a[i].print();
		}
		cout << endl << endl;
	}
	void printtrainer()
	{
		cout << "Trainers " << endl;
		for (int i = 0; i < trainersize; i++)
		{
			b[i].print();
		}
		cout << endl << endl;
	}
	void printeq()
	{
		cout << "Equipments " << endl;
		for (int i = 0; i < eqsize; i++)
		{
			c[i].print();
		}
	}
	void printex()
	{
		cout << endl << endl;
		cout << "Exercise Plans " << endl;
		for (int i = 0; i < epsize; i++)
		{
			d[i].print();
		}
	
	}
	void printsub()
	{
		cout << "Subscriptions " << endl;
		for (int i = 0; i < subsize; i++)
		{
			e[i].print();
		}
	}

	void add()
	{
		int ch, index, id;
		int id_temp;
		string name = "*", add = "*", phone = "*", email = "*";
		system("cls");
		cout << "What do you want to ADD? \n0)Customer \n1)Trainers \n2)Equipments\n3)Exercise Plans \n4)Subscription \n Choice : ";
		cin >> ch;
		if (ch == 0)
		{
			cout << "Customer ID to add Object : ";
			cin >> id_temp;

			cin.ignore();
			cout << "Enter Name : ";
			getline(cin, name);

			cout << "Enter Address : ";
			getline(cin, add);

			cout << "Enter Phone Number : ";
			getline(cin, phone);

			cout << "Enter Email : ";
			getline(cin, email);

			extend(a, custsize);
			a[custsize].entry(id_temp, name, add, phone, email);
			custsize++;
		}
		else if (ch == 1)
		{
			cout << " Trainer ID to add Object : ";
			cin >> id_temp;

			cin.ignore();
			cout << "Enter Trainer Name : ";
			getline(cin, name);

			extend(b, trainersize);
			b[trainersize].entry(id_temp, name);
			trainersize++;
		}
		else if (ch == 2)
		{
			cout << "Equipment ID to add Object : ";
			cin >> id_temp;

			cin.ignore();
			cout << "Enter Name : ";
			getline(cin, name);

			extend(c, eqsize);
			c[eqsize].entry(id_temp, name);
			eqsize++;
		}
		else if (ch == 3)
		{
			int trainid = -1, eqid = -1, duration = -1;
			cout << " New Plan ID to add Object : ";
			cin >> id_temp;

			if (findid(d, epsize, id_temp) != -1)
			{
				cout << " This ID Already exist. Kindly enter a new one : ";
				cin >> id_temp;
			}

			cout << "Kindly Enter the  Trainer ID :";
			cin >> trainid;

			if (findid(b, trainersize, trainid) == -1)
			{
				cout << "Kindly Enter the Correct  Trainer ID Which should exist in the Database :";
				cin >> trainid;
			}

			cout << "Kindly Enter the  Equipment ID :";
			cin >> eqid;

			if (findid(c, eqsize, eqid) == -1)
			{
				cout << "Kindly Enter the Correct  Trainer ID Which should exist in the Database :";
				cin >> trainid;
			}
			
			cout << "Kindly Enter the NEW  Duration :";
			cin >> duration;

			extend(d, epsize);
			d[epsize].entry(id_temp, trainid, eqid, duration);
			epsize++;
		}
		else if (ch == 4)
		{
			int custid = -1, planid = -1;
			cout << " Subscription ID to add Object : ";
			cin >> id_temp;
		
			if ((findid(e, eqsize, id_temp) != -1))
			{
				cout << "Kindly Enter the New Subscription ID :";
				cin >> id_temp;
			}
			cin.ignore();

			cout << "Kindly Enter the Date in format 26/10/2020 :";		///date input
			getline(cin, name);

			cout << "Kindly Enter the Customer ID :";
			cin >> custid;

			if (findid(a, custsize, custid) == -1)
			{
				cout << "Kindly Enter the Correct  Customer ID Which should exist in the Database :";
				cin >> custid;
			}
			cout << "Kindly Enter the Plan ID :";
			cin >> planid;

			if (findid(d, epsize, planid) == -1)
			{
				cout << "Kindly Enter the Correct  Plan ID Which should exist in the Database :";
				cin >> planid;

			}
			extend(e, subsize);
			e[subsize].entry(id_temp, custid, planid, name);
			subsize++;
		}
		else
		{
			cout << "Wrong Option .\n";
		}
	}
	void modify()
	{
		int ch = 0, index, id;
		system("cls");
		cout << "What do you want to modify? \n0)Customer \n1)Trainers \n2)Equipments\n3)Exercise Plans \n4)Subscription \n Choice : ";
		cin >> ch;
		if (ch == 0)
		{
			cout << "Enter ID of the Customer : ";
			cin >> id;
			index = findid(a, custsize, id);
			if (index >= 0)
			{
				a[index].modifydata();
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else if (ch == 1)
		{
			cout << "Enter ID of the Trainer : ";
			cin >> id;
			index = findid(b, trainersize, id);
			if (index >= 0)
			{
				b[index].modifydata();
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}

		}
		else if (ch == 2)
		{
			cout << "Enter ID of the Equipment : ";
			cin >> id;
			index = findid(c, eqsize, id);
			if (index >= 0)
			{
				c[index].modifydata();
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else if (ch == 3)
		{
			cout << "Enter ID of the Exercise Plan : ";
			cin >> id;
			index = findid(d, epsize, id);
			if (index >= 0)
			{
				d[index].modifydata();
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else if (ch == 4)
		{
			cout << "Enter ID of the Subscription : ";
			cin >> id;
			index = findid(e, subsize, id);
			if (index >= 0)
			{
				e[index].modifydata();
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else
		{
			cout << "Wrong Option .\n";
		}

	}
	void dataremove()
	{
		int ch = 0, index, id;
		system("cls");
		cout << "What Type of class Object do you want to Remove? \n0)Customer \n1)Trainers \n2)Equipments\n3)Exercise Plans \n4)Subscription \n Choice : ";
		cin >> ch;
		if (ch == 0)
		{
			cout << "Enter ID of the Customer to Remove : ";
			cin >> id;
			index = findid(a, custsize, id);
			if (index >= 0)
			{
				remove(a, custsize, index);
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else if (ch == 1)
		{
			cout << "Enter ID of the Trainer to remove : ";
			cin >> id;
			index = findid(b, trainersize, id);
			if (index >= 0)
			{
				remove(b, trainersize, index);
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else if (ch == 2)
		{
			cout << "Enter ID of the Equipment to remove : ";
			cin >> id;
			index = findid(c, eqsize, id);
			if (index >= 0)
			{
				remove(c, eqsize, index);
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else if (ch == 3)
		{
			cout << "Enter ID of the Exercise Plan to remove : ";
			cin >> id;
			index = findid(d, epsize, id);
			if (index >= 0)
			{
				remove(d, epsize, index);
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else if (ch == 4)
		{
			cout << "Enter ID of the Subscription to Remove : ";
			cin >> id;
			index = findid(e, subsize, id);
			if (index >= 0)
			{
				remove(e, subsize, index);
			}
			else
			{
				cout << "\nEntered ID doesnot match any entered data.\n";
			}
		}
		else
		{
			cout << "Wrong Option .\n";
		}

	}

	void avail()
	{
		int trainid, eqid, tempid, subid;
		cout << "Enter the Trainer ID you want to use : ";
		cin >> trainid;
		int index = findid(b, trainersize, trainid);
		if (index >= 0)
		{
			cout << "Enter the Equipment ID you want to use : ";
			cin >> eqid;
			index = findid(c, eqsize, eqid);
			if (index >= 0)
			{
				int indexofplan = checkplans(d, epsize, trainid, eqid);
				if (indexofplan >= 0)
				{
					string newdate;
					cout << "Kindly Enter the Date to Check Availability of this Plan. Format should be like 26/10/2003 : ";
					cin >> newdate;

					date temp;
					temp.entry(newdate);

					if (checkdate(e, subsize, newdate))
					{
						cout << "This Trainer & Equipment is Available. Now Kindly give your Customer ID : ";
						cin >> tempid;
						if (findid(a, custsize, tempid) == -1)
						{
							cout << "This Customer Doesnot exist.Kindly Re-enter Your ID : ";
							cin >> tempid;
						}

						cout << "Now Kindly Enter Subscription ID : ";
						cin >> subid;
						extend(e, subsize);
						e[subsize].entry(subid, tempid, retplanid(e, subsize, indexofplan), temp);
						subsize++;
						cout << "Your subscription is added.\n";
					}
				}
				else
				{
					cout << "This Plan is not Available.Kindly Choose other Instructor and Equipment or add it in the plan menu first.\n";
				}
			}
			else
			{
				cout << "This Equipment Does not Exist.\n";
			}
		}
		else
		{
			cout << "This trainer Does not Exist.\n";
		}

	}

	void inquirycust()
	{
		system("cls");
		cout << "\n----------------------------------------------------Inquiry Menu----------------------------------------------" << endl;
		int custid, indexofsub, planfromsub, cusid;
		cout << "Kindly Enter the Customer ID To Get Sechdule : ";
		cin >> custid;
		bool found = false;
		string username;
		for (int i = 0; i < subsize; i++)
		{
			if (e[i].getcustid() == custid)
			{
				indexofsub = i;
				planfromsub = e[i].getplanid();
				cusid = e[i].getcustid();
				found = true;
				if (found)
				{
					int indexfromep = findid(d, epsize, planfromsub);
					if (indexfromep >= 0)
					{
						int duration, equip, indexid, trid;
						string trainername, eqname;
						equip = d[indexfromep].geteqid();
						trid = d[indexfromep].gettrainid();
						duration = d[indexfromep].getduration();
						indexid = findid(c, eqsize, equip);
						eqname = c[indexid].geteqname();
						indexid = findid(b, trainersize, trid);
						trainername = b[indexid].gettranname();
						cout << "Mr " << a[findid(a, custsize, cusid)].getcustname() << endl;
						cout << "You have to do " << eqname << " for " << duration << " minutes with Trainer" << trainername << ". You have subscribed for Plan " << planfromsub << endl;
					}
					else
					{
						cout << "Data in Subscription Table is Faulty because the Exercise Plan doesnot exist with id " << planfromsub << " in Exercise Plan Table." << endl << endl;
					}
				}
			}
		}
		if (!found)
		{
			cout << "This Customer ID  was not in Subscription Table.You haven't Subscribe to any Plan Yet." << endl;
		}
	}

	void writetofile()
	{
		ofstream fout("customers.txt");
		for (int i = 0; i < custsize; i++)
		{
			if (i != 0)
			{
				fout << endl;
			}
			fout << a[i].getid() << endl << a[i].getcustname() << endl << a[i].getcustaddress() << endl << a[i].getcustphone() << endl << a[i].getcustemail();
		}
		fout.close();

		ofstream fout1("trainers.txt");
		for (int i = 0; i < trainersize; i++)
		{
			if (i != (trainersize - 1))
			{
				fout1 << b[i].gettainerid() << "  " << b[i].gettranname() << endl;
			}
			else
			{
				fout1 << b[i].gettainerid() << "  " << b[i].gettranname();
			}
		}
		fout1.close();

		ofstream fout2("equipments.txt");
		for (int i = 0; i < eqsize; i++)
		{
			if (i != (eqsize - 1))
			{
				fout2 << c[i].getid() << endl << c[i].geteqname() << endl;
			}
			else
			{
				fout2 << c[i].getid() << endl << c[i].geteqname();
			}
		}
		fout2.close();

		ofstream fout3("excercisePlans.txt");
		for (int i = 0; i < epsize; i++)
		{
			if (i != (epsize - 1))
			{
				fout3 << d[i].getid() << " " << d[i].gettrainid() << " " << d[i].geteqid() << " " << d[i].getduration() << endl;
			}
			else
			{
				fout3 << d[i].getid() << " " << d[i].gettrainid() << " " << d[i].geteqid() << " " << d[i].getduration();
			}
		}
		fout3.close();

		ofstream fout4("subscriptions.txt");
		for (int i = 0; i < subsize; i++)
		{
			if (i == subsize - 1)
			{
				fout4 << e[i].getid() << " " << e[i].datestr() << " " << e[i].getcustid() << " " << e[i].getplanid();
			}
			else
			{

				fout4 << e[i].getid() << " " << e[i].datestr() << " " << e[i].getcustid() << " " << e[i].getplanid() << endl;
			}
		}
		fout4.close();

	}
};

int main()
{
	int custsize = 0;
	customer* cstmr = new customer[custsize];
	readcustdatafromfile(cstmr, custsize);

	int trainsize = 0;
	trainer* tnr = new trainer[trainsize];
	readtrainerdatafromfile(tnr, trainsize);

	int eqsize = 0;
	equipment* eqp = new equipment[eqsize];
	readeqdatafromfile(eqp, eqsize);

	int epsize = 0;
	exerciseplan* ep = new exerciseplan[eqsize];
	readepdatafromfile(ep, epsize);

	int subsize = 0;
	subscription* sub = new subscription[subsize];
	readsubdatafromfile(sub, subsize);

	errorcheck = true;


	gym obj(cstmr, tnr, eqp, ep, sub, custsize, trainsize, eqsize, epsize, subsize);


	bool run = true;
	int ch;
	while (run)
	{
		menu();
		cout << "Choice : ";
		cin >> ch;
		if (ch == 1)
		{
			system("cls");
			int tempch = -1;
			cout << "Enter \n 0) Add 1) Edit 2) Remove\nChoice : ";
			cin >> tempch;
			if (tempch == 0)
			{
				obj.add();
			}
			else if (tempch == 1)
			{
				obj.modify();
			}
			else if (tempch == 2)
			{
				obj.dataremove();
			}
		}
		else if (ch == 2)
		{
			obj.avail();
		}
		else if (ch == 3)
		{
			cout << "Customer Inquiry " << endl;
				obj.inquirycust();
		}
		
		else if (ch == 4)
		{
			int test;
			cout << "Do you want to save Data into the File 1)Yes 0)NO : ";
			cin >> test;
			if (test == 1)
			{
				obj.writetofile();
				cout << "Data saved.";
			}
			break;
		}
		else if (ch == 5)
		{
			obj.printalldata();
		}
		else
		{
			cout << "Wrong Option. ";
		}
		system("pause");
	}


	if (cstmr != nullptr)
	{
		delete[]cstmr;
	}
	if (tnr != nullptr)
	{
		delete[]tnr;
	}
	if (eqp != nullptr)
	{
		delete[]eqp;
	}
	if (ep != nullptr)
	{
		delete[]ep;
	}
	if (sub != nullptr)
	{
		delete[] sub;
	}
}