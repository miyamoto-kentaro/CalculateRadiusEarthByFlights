#ifndef CONSTANTS_H
#define CONSTANTS_H

// ���� �}�N����` ����
#define PI 3.14159265358979323846  // �~����
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0)     // �x�����W�A��
#define FT_TO_M(ft) ((ft) * 0.3048)           // �t�B�[�g�����[�g��
#define KTS_TO_MPS(kts) ((kts) * 0.514444)   // �m�b�g�����[�g�����b

// �o�x��phi(0<phi<2PI) �O���j�b�W�V����� 0PI
#define Longitude_TO_PHI(longitude) ((longitude) * PI / 180.0)

// �ܓx��phi(0<phi<PI) �ԓ��� PI/2
#define Latitude_TO_THETA(latitude) (PI/2 - (latitude) * PI / 180.0)

#define EARTH_RADIUS_M 6371000.0  // �����̒n���̔��a�i���[�g���j


#endif // CONSTANTS_H
