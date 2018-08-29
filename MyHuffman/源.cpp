#include<iostream>
#include<vector>
#include<string>

using namespace std;
//1 ���峣��������һ�����������������λ�����0010 0000(2^5)�����������ڵ�ͱ����������0100 0000 0000(2^10)��
const int INF = 1000000000;
const int maxBit = 1 << 5;
const int maxNode = 1 << 10;
const int maxCode = 1 << 10;


struct Node {
	string value;
	float weight;
	int parent;
	int lchild;
	int rchild;
};
struct Code {
	int bit[maxBit];
	int start;
	string value;
};

int n;
Node huffmanNode[maxNode];
Code huffmanCode[maxCode];



//��ʼ�����������ڵ㣨2*n-1��
void initialHuffmanTree(){
	for (int i = 0; i<2 * n - 1; i++) {
		huffmanNode[i].value = " ";
		huffmanNode[i].weight = 0;
		huffmanNode[i].parent = -1;
		huffmanNode[i].lchild = -1;
		huffmanNode[i].rchild = -1;
	}
}


void CreatHuffmanTree() {
	for (int i = 0; i<n - 1; i++) {    //����ԭʼҶ�ڵ㣨�������ַ��������n-1���ϳɸ��ڵ�
		int w1 = INF;    //ÿһ�γ�ʼ����СȨֵ
		int w2 = INF;    //ÿһ�γ�ʼ����СȨֵ
		int index1 = 0;
		int index2 = 0;

		for (int j = 0; j<n + i; j++) {
			if (huffmanNode[j].weight<w1&&huffmanNode[j].parent == -1) {
				w2 = w1;    //�ҵ��µ���Сֵ�󣬽�֮ǰ����Сֵw1�����Ϊ��Сֵw2
				index2 =index1;
				w1 = huffmanNode[j].weight;   //�µ���Сֵ
				index1 = j;
			}
			else if (huffmanNode[j].weight<w2&&huffmanNode[j].parent == -1) {
				w2 = huffmanNode[j].weight;
				index2 = j;
			}
		}
		huffmanNode[index1].parent = n + i;
		huffmanNode[index2].parent = n + i;
		huffmanNode[n + i].weight = w1 + w2;
		huffmanNode[n + i].lchild = index1;   //ע�⣺�ڶ���ʱparent��lchild��rchild����int
		huffmanNode[n + i].rchild = index2;   //�����ݣ�������ָ�룬����Ϊ�˽�ʡ�ռ䲢�Ҳ�����

	}
}

//����
//Huffman���뷽ʽΪÿ���ַ��������ڽڵ�����huffmanNode�дӸ��ַ��ڵ㿪ʼ������׷���丸�ڵ㣬���ýڵ����丸�ڵ�����ӽڵ㣬��������������[n-1]λ��0�������丸�ڵ�����ӽڵ㣬�������������ġ�n-1��λ��1���ٶԸ��ڵ��Ҹ��ڵ㣬һֱ����׷�ݣ���start--������ÿһλ�����bitֵŪ�����ֱ���丸�ڵ㲻���ڣ�parent=-1��������ڵ㣩����Ϊ��ÿһ���ַ���start����Ϊn-1����Ϊn���ַ��Ļ����������Ϊn-1������ÿһλbitֵ�ǴӺ���ǰ׷�ݣ���ʱ��startֵ��������Ļ���������Ӧ�ӵ�startλ��ʼ�������Ϊǰ���ֵû��ȷ���ˡ�ֻ�д�start��ǰֵ��n-1���������ı���ֵ��
void HuffmanEncoding() {
	int  child, parent;
	Code cd;
	for (int i = 0; i<n; i++) {
		cd.value = huffmanNode[i].value;
		cd.start = n - 1;
		child = i;
		parent = huffmanNode[child].parent;
		while (parent != -1) {
			if (huffmanNode[parent].lchild == child) {
				cd.bit[cd.start] = 0;
			}
			else if (huffmanNode[parent].rchild == child) {
				cd.bit[cd.start] = 1;
			}
			cd.start--;
			child = parent;
			parent = huffmanNode[child].parent;
		}

		//����ÿһ���ַ��Ļ���������
		for (int j = cd.start + 1; j<n; j++)
			huffmanCode[i].bit[j] = cd.bit[j];
		huffmanCode[i].value = cd.value;  //��������������ԭʼ�ַ�
		huffmanCode[i].start = cd.start;   //֮���������ֵʱҪ��start+1λ��ʼ����
	}
}
//��ӡ����������
void PrintHuffman() {
	for (int i = 0; i < n; i++) {
		cout << "��" << i + 1 << "���ַ�" << huffmanNode[i].value << "��Huffman������:";
		for (int j = huffmanCode[i].start + 1; j < n; j++) {
			cout << huffmanCode[i].bit[j];
		}
		cout << "������ʼֵ�ǣ�" << huffmanCode[i].start << endl;
	}
}


//����
//��0/1����s��bitλ����s[0]-s.length()�ӻ��������ĸ��ڵ㿪ʼ���±���ֱ���ҵ�Ҷ�ӽڵ㣬����Ҷ�ӽڵ���ַ���ԭ�룩�����������ҵ�һ��ԭ�������ٶԵ�ǰ��s[i]�Ӹ��ڵ����±�����ÿ����һ��Ҷ�ӽڵ�ͽ��ַ�����������ֱ������������ĩ�ˣ���������е�ֵ���Ƕ�Ӧ��ԭ�롣���ǵ�������ĩ��ȴ����ȱʧ�����жϽ��롣
void HuffmanDecoding(string s) {
	vector<string> v;  //��Ž��������һ����ԭ��
	int ok = 1;   //��־λ��Ϊ1��ʾ�������룬Ϊ0��ʾ��������
	for (int i = 0; i<s.length();) {
		int x = 2 * n - 1 - 1;         //�Ӹ��ڵ㿪ʼ������ÿ������һ��Ҷ�ӽڵ㣬��Ҷ�ӽ�
									   //���ַ�����vector�С�
		while (huffmanNode[x].lchild != -1 && huffmanNode[x].rchild != -1) {
			if (s[i] == '0')
				x = huffmanNode[x].lchild;
			else if(s[i] =='1')
				x = huffmanNode[x].rchild;
			i++;
			//δ�ҵ�Ҷ�ӽڵ�
			if (i == s.length() && huffmanNode[x].lchild != -1) {
				ok = 0;
				break;  //�˳�ѭ��
			}
		} //����Ҷ�ӽڵ������ĩ�ˣ�while����
		  //�ҵ�Ҷ�ӽڵ㣬��Ҷ�ӽڵ��е�ԭʼ�ַ�����������
		if (ok) {
			v.push_back(huffmanNode[x].value);
		}
	}   //����������ַ�������vector�У�forѭ������

		//�������ַ������
	if (ok) {
		for (int i = 0; i<v.size(); i++)
			cout <<v[i];
		cout << endl;
	}
	else
		cout << "����ʧ�ܣ�"<< endl;
}

//������

int main() {
	//����
	while (true) {
		cout << "�������ַ���������";
		cin >> n;
		if (!n) {
			break;
		}

		// ��ʼ��Huffman��
		initialHuffmanTree();

		for (int i = 0; i<n; i++) {
			cout << "�������" << i + 1 << "���ַ�������Ȩֵ";
			cin >> huffmanNode[i].value >> huffmanNode[i].weight;
			//�������Huffman���Ľڵ���
		}
		CreatHuffmanTree();

		HuffmanEncoding();

		PrintHuffman();

		//����
		while (true) {
			cout << "���������������������0 / 1���л�q������һ�α��룺";
			string s;
			cin >> s;
			if (s[0] == 'q') {    //����δ�������е����
				cout << endl;
				break;
			}

			cout << "�����������:" << s << endl;
			cout << "����Ľ���ǣ�";
			HuffmanDecoding(s);
		}
	}
	return 0;
}