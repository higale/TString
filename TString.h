/**
*  @file TString.h
*  @brief TCHAR�ַ�����������ļ�
*
*  ���ļ�����˶�TCHAR�ַ����� TString �Ķ���
*
*  @version 1.0
*  @author HeatoN
*  @date 2007-03-04
*  
*  Copyright (c) 2007, Yaphon
*  All rights reserved.
*/
#ifndef _TSTRING_H_
#define _TSTRING_H_

#pragma once

#pragma warning(disable : 4996)	// ����ȫ�ַ�������

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
//#include "stdafx.h"
//#include "stdarg.h"

//! ����ַ�������
//const int TSTRING_MAX_CHARS = 2048;

//! Format�ĸ�ʽ������󳤶�
const int TSTRING_MAX_FORMAT_CHARS = 102400;

/**
*  @brief TCHAR�ַ�����
*
*  ���������TCHAR�ַ����ĳ��ò���,ʹ�÷�����MFC����CString����
*/
class TString
{
protected:	// ��������
	TCHAR* m_lpszStr;		//!< C����ַ���,ָ�����ʵ���ַ�������
	int     m_nSize;		//!< �ַ����ĳ���,����NULL�ַ�
	
public:	// ���켰����
	
	/**
	*  @brief Ĭ�Ϲ��캯��
	*
	*  �������κβ���������ʱ,ʹ�ñ����캯��, ��:\n
	*  TString strTemp;
	*
	*  @return ��
	*/
	TString()
		:m_nSize( 0 ),
		m_lpszStr( NULL )
	{
		m_nSize = 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		m_lpszStr[ 0 ] = _T( '\0' );
	}
	
	/**
	*  @brief �������캯��
	*
	*  ����һ���������㹻�ַ��Ŀ��ַ���
	*
	*  @param nLen �ַ�������󳤶�
	*  @return ��
	*/
	TString( const int & nLen )
		:m_nSize( 0 ),
		m_lpszStr( NULL )
	{
		m_nSize = nLen + 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		::memset( m_lpszStr, 0, m_nSize * sizeof( TCHAR ) );
	}
	
	/**
	*  @brief �ַ������Ĺ��캯��
	*
	*  ���ַ�����������ʵ��
	*
	*  @param chData �ַ�
	*  @return ��
	*/
	TString( const TCHAR chData )
		:m_nSize( 0 ),
		m_lpszStr( NULL )
	{
		m_nSize = 2;
		m_lpszStr = new TCHAR[ m_nSize ];
		m_lpszStr[0] = chData;
		m_lpszStr[1] = _T( '\0' );
	}
	
	/**
	*  @brief C����ַ��������Ĺ��캯��
	*
	*  ��C����ַ�������������ʵ��, ��:\n
	*  TString strTemp( _T( "Temp" );\n
	*  TString strAbc = _T( "abc" );
	*
	*  @param lpszData C����ַ���
	*  @return ��
	*/
	TString( const TCHAR * lpszData )
		:m_nSize( 0 ),
		m_lpszStr( NULL )
	{
		m_nSize = ::_tcslen( lpszData ) + 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		::_tcscpy( m_lpszStr, lpszData );
	}
	
	/**
	*  @brief ���ƹ��캯��
	*
	*  ʹ����һ����ʵ����Ϊ���������µ���ʵ��, ��:\n
	*  TString m_lpszStrA = _T( "abc" );\n
	*  TString m_lpszStrB( m_lpszStrA );
	*
	*  @param strData ���ڸ��Ƶ���ʵ��
	*  @return ��
	*/
	TString( const TString &strData )
		:m_nSize( 0 ),
		m_lpszStr( NULL )
	{
		m_nSize = strData.Length( ) + 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		::_tcscpy( m_lpszStr, strData.m_lpszStr );
	}
	
	/**
	*  @brief ��������
	*
	*  ��׼��������
	*
	*  @return 
	*/
	~TString( )
	{
		delete [] m_lpszStr;
		m_lpszStr = NULL;
	}
	
	
public:	//���ز�����	
	
	/**
	*  @brief =�Ų��������� ( TString��ʵ�� )
	*
	*  �Ա������һ��ʵ���Ա�ʵ����ֵ, ��:\n
	*  TString m_lpszStrA = _T( "aaa" );\n
	*  TString m_lpszStrB = m_lpszStrA;
	*
	*  @param strData �������һ��ʵ��
	*  @return ʵ������
	*/
	TString& operator = ( const TString &strData )
	{
		return *this = strData.m_lpszStr;
	}
	
	/**
	*  @brief =�Ų��������� ( �ַ� )
	*
	*  ���ַ��Ա����ʵ����ֵ
	*
	*  @param chData �ַ�
	*  @return ʵ������
	*/
	TString& operator = ( const TCHAR chData )
	{
		delete [] m_lpszStr;
		m_lpszStr = NULL;
		m_nSize = 2;
		m_lpszStr = new TCHAR[ m_nSize ];
		m_lpszStr[0] = chData;
		m_lpszStr[1] = _T( '\0' );
		return *this;
	}
	
	/**
	*  @brief =�Ų��������� ( C����ַ��� )
	*
	*  ��C����ַ����Ա����ʵ����ֵ, ��:\n
	*  TString m_lpszStrA = _T( "aaa" );\n
	*
	*  @param lpszData C����ַ���
	*  @return ʵ������
	*/
	TString& operator = ( const TCHAR * lpszData )
	{
		if( ::_tcscmp( m_lpszStr, lpszData ) == 0 )
		{
			return *this;
		}
		
		delete [] m_lpszStr;
		m_lpszStr = NULL;
		m_nSize = ::_tcslen( lpszData ) + 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		::_tcscpy( m_lpszStr, lpszData );
		
		return *this;
	}	
	
	/**
	*  @brief ==����������
	*
	*  ��C����ַ����Ƚ�
	*
	*  @param lpszData C����ַ���
	*  @return �����C����ַ�����ȫ���,����TRUE,����,����FALSE
	*/
	BOOL operator == ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) == 0 && Length() == static_cast<int>( ::_tcslen( lpszData ) );
	}
	
	/**
	*  @brief !=����������
	*
	*  ��C����ַ����Ƚ�
	*
	*  @param lpszData C����ַ���
	*  @return �����C����ַ�������ͬ,����TRUE,����,����FALSE
	*/
	BOOL operator != ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) != 0 || Length() != static_cast<int>( _tcslen( lpszData ) );
	}
	
	/**
	*  @brief <����������
	*
	*  ��C����ַ����Ƚ�, �Ƚ���ͨ��ƽ̨�ı�����ɵ�,�� ASCII���, ��ͬ��ƽ̨, ���ܲ�����ͬ�Ľ��
	*
	*  @param lpszData C����ַ���
	*  @return �����ʵ��С�ڲ����ṩ���ַ���,����TRUE,����,����FALSE
	*/
	BOOL operator < ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) == -1;
	}
	
	/**
	*  @brief <=����������
	*
	*  ��C����ַ����Ƚ�, �Ƚ���ͨ��ƽ̨�ı�����ɵ�,�� ASCII���, ��ͬ��ƽ̨, ���ܲ�����ͬ�Ľ��
	*
	*  @param lpszData C����ַ���
	*  @return �����ʵ��С�ڻ���ڲ����ṩ���ַ���,����TRUE,����,����FALSE
	*/
	BOOL operator <= ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) != 1;
	}
	
	/**
	*  @brief >����������
	*
	*  ��C����ַ����Ƚ�, �Ƚ���ͨ��ƽ̨�ı�����ɵ�,�� ASCII���, ��ͬ��ƽ̨, ���ܲ�����ͬ�Ľ��
	*
	*  @param lpszData C����ַ���
	*  @return �����ʵ�����ڲ����ṩ���ַ���,����TRUE,����,����FALSE
	*/
	BOOL operator > ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) == 1;
	}
	
	/**
	*  @brief >=����������
	*
	*  ��C����ַ����Ƚ�, �Ƚ���ͨ��ƽ̨�ı�����ɵ�,�� ASCII���, ��ͬ��ƽ̨, ���ܲ�����ͬ�Ľ��
	*
	*  @param lpszData C����ַ���
	*  @return �����ʵ�����ڻ���ڲ����ṩ���ַ���,����TRUE,����,����FALSE
	*/
	BOOL operator >= ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) != -1;
	}
	
	/**
	*  @brief +����������
	*
	*  ��ɺ�C����ַ�������� ( �����ַ��� )
	*
	*  @param lpszData C����ַ���
	*  @return ��Ӻ����ʵ�� ( ���Ӻ���ַ��� )
	*/
	TString operator + ( const TCHAR * lpszData )
	{
		TCHAR* szTemp;
		szTemp = new TCHAR[ Length() + ::_tcslen( lpszData ) + 1 ];
		::_tcscpy( szTemp, m_lpszStr );
		::_tcscat( szTemp, lpszData );
		TString strTemp( szTemp );
		delete [] szTemp;
		szTemp = NULL;
		return strTemp;
	}
	
	/**
	*  @brief ��Ա + ����������( C����ַ��� + TString )
	*
	*  ���C����ַ����ͱ���ʵ�������
	*
	*  @param lpszLeft C����ַ���
	*  @param strRight �����ʵ��
	*  @return ��Ӻ����ʵ�� ( ���Ӻ���ַ��� )
	*/
	friend TString operator + ( TCHAR * lpszLeft, const TString &strRight )
	{
		TCHAR* szTemp;
		szTemp = new TCHAR[ strRight.Length() + ::_tcslen( lpszLeft ) + 1 ];
		::_tcscpy( szTemp, lpszLeft ) ;
		::_tcscat( szTemp, strRight.m_lpszStr );
		TString strTemp( szTemp );
		delete [] szTemp;
		szTemp = NULL;
		return strTemp;
	}
	
	/**
	*  @brief +=����������
	*
	*  ����һ���ַ������ӵ�������β�� ( �����ַ��� )
	*
	*  @param lpszData C����ַ���
	*  @return ���Ӻ����ʵ�� ( ���Ӻ���ַ��� )
	*/
	void operator += ( const TCHAR * lpszData )
	{
		TCHAR* szTmp;
		szTmp = new TCHAR[ m_nSize ];
		::_tcscpy( szTmp, m_lpszStr );
		m_nSize += ::_tcslen( lpszData );
		delete [] m_lpszStr;
		m_lpszStr = NULL;
		m_lpszStr = new TCHAR[ m_nSize ];
		::_tcscpy( m_lpszStr, szTmp);
		::_tcscat( m_lpszStr, lpszData);
		delete [] szTmp;
		szTmp = NULL;
	}
	
public:	// �Ӵ�����
	
	/**
	*  @brief ȡ���ַ���
	*
	*  ��ָ��λ����ȡָ�����ȵ����ַ���
	*
	*  @param nIndex ���ַ����Ŀ�ʼλ��
	*  @param nCount ���ַ����ĳ���
	*  @return ���ַ���
	*/
	TString SubStr( int nIndex, int nCount ) const
	{
		TString strTmp;
		int i;
		
		// �жϴ�������ַ����Ŀ�ʼλ���Ƿ���Ч :
		if ( ( nIndex <= 0 ) || ( nIndex >= m_nSize ) )
		{
			return strTmp;
		}
		// ���� ( �жϴ�������ַ����Ŀ�ʼλ���Ƿ���Ч )
		
		// �жϴ�������ַ����ĳ����Ƿ���Ч :
		if ( ( nIndex + nCount ) >= m_nSize )
		{
			nCount = m_nSize - nIndex;
		}
		// ���� ( �жϴ�������ַ����ĳ����Ƿ���Ч )
		
		TCHAR* s = new TCHAR[ nCount + 1 ];
		nIndex --;
		
		for ( i = 0; i < nCount; i++ )
		{
			s[ i ] = m_lpszStr[ nIndex++ ];
		}
		s[ i ] = _T( '\0' );
		
		strTmp = s;
		
		delete [] s;
		s = NULL;
		
		return strTmp;
	}
	
	/**
	*  @brief �������ַ���
	*
	*  ��ָ��λ�ò���һ�����ַ���
	*
	*  @param lpszData Ҫ��������ַ���
	*  @param nIndex   �����λ��
	*  @return ��
	*/
	void Insert( const TCHAR * lpszData, int nIndex )
	{
		// �жϴ���Ĳ����λ���Ƿ���Ч :
		if ( ( nIndex <= 0 ) || ( nIndex > m_nSize ) )
		{
			return;
		}
		// ���� ( �жϴ�������ַ����Ŀ�ʼλ���Ƿ���Ч )
		
		m_nSize += ::_tcslen( lpszData );
		
		TCHAR* s = new TCHAR[ m_nSize ];
		int i, j, k;
		
		for ( i=0; i < nIndex - 1; i++ )
		{
			s[i] = m_lpszStr[i];
		}
		
		for ( j = 0; j < static_cast<int>( ::_tcslen( lpszData ) ); j++ )
		{
			s[ i + j ] = lpszData[ j ];
		}
		
		for ( k = 0; ( i + j + k ) < ( m_nSize - 1 ); k++ )
		{
			s[ i + j + k ] = m_lpszStr[ i + k ];
		}
		s[ i + j + k ] = _T( '\0' );
		
		delete [] m_lpszStr;
		m_lpszStr = new TCHAR[ m_nSize ];
		::_tcscpy( m_lpszStr, s );
		
		delete [] s;
		s = NULL;
	}
	
	/**
	*  @brief ɾ�����ַ���
	*
	*  ��ָ��λ��ɾ��ָ�����ȵ����ַ���
	*
	*  @param nIndex Ҫɾ���Ӵ�����ʼλ��
	*  @param nCount Ҫɾ���Ӵ��ĳ���
	*  @return ��
	*/
	void Remove( int nIndex, int nCount )
	{
		int i;

		// �жϴ����Ҫɾ���Ӵ�����ʼλ���Ƿ���Ч :
		if ( ( nIndex <= 0 ) || ( nIndex >= m_nSize ) )
		{
			return;
		}
		// ���� ( �жϴ����Ҫɾ���Ӵ�����ʼλ���Ƿ���Ч )
		
		// �жϴ����Ҫɾ���Ӵ��ĳ����Ƿ���Ч :
		if ( ( nIndex + nCount ) > m_nSize )
		{
			nCount = m_nSize - nIndex;
		}
		// ���� ( �жϴ����Ҫɾ���Ӵ��ĳ����Ƿ���Ч )
		
		for ( i = nIndex - 1; i < ( m_nSize - nCount - 1 ); i++ )
		{
			m_lpszStr[ i ] = m_lpszStr[ i + nCount ];
		}
		m_lpszStr[ i ] = _T( '\0' );
		
		m_nSize -= nCount;
	}
	
public: // �±꼰ǿ������ת������

	/**
	*  @brief �±�����
	*
	*  ����ַ��������ģ�����
	*
	*  @param n �����±�
	*  @return ָ���±���ַ�����
	*/
	TCHAR & operator [] ( int n )
	{
		if ( ( m_nSize == 1 ) || ( n < 0 ) )
		{
			return m_lpszStr[0];
		}
		else if ( n < ( m_nSize - 1 ) )
		{
			return m_lpszStr[ n ];
		}
		else
		{
			return m_lpszStr[ m_nSize - 1 ];
		}
	}
	
	
	/**
	*  @brief ǿ��ת����const TCHAR*��
	*
	*  ���ڱ����������صĴ���, ������ʹ��TCHAR*һ��ʹ�ñ����ʵ��,\n
	*  Ϊ�˷�ֹ�ƻ���Ա����, ���ص�ָ��ʹ��const����������.\n
	*  ����д������ʱӦע��, ����ת��ʱʹ����const, ���Բ���ֱ�ӽ�\n
	*  ��д����, ���ȷ��Ҫִ��д��, ����ʹ������ת��:\n
	*  TString m_lpszStrTmp = _T( "abcd" );\n
	*  const_cast<TCHAR*>( static_cast<const TCHAR*>(m_lpszStrTmp) );\n
	*  ͬʱҪע��,д��ʱ��Ҫ������ʹ�õ����ݳ���.\n
	*  ( ����д�������ֱ�������ĳ�Ա������, ��Υ������ķ�װԭ��,Ӧ����������������ĳ��� )
	*
	*  @return operator _const TCHAR*
	*/
	operator const TCHAR* ( ) const
	{
		return m_lpszStr;
	}
	
public:	//��������
	
	/**
	*  @brief ��ʽ���ַ���
	*
	*  ʹ�÷��������� sprintf ����
	*
	*  @param lpszFormat ��ʽ���ַ���
	*  @param ... Ҫ��ʽ�ı����б�
	*  @return int ��ʽ������ַ�������
	*/
	int Format( const TCHAR * lpszFormat, ... )
	{
		va_list ap;
		int nLen;
		TCHAR * szTmp;
		int i;
		
		for( i = 1; i <= 1024; i++ )
		{
			szTmp = new TCHAR[ 1024 * i + 1 ];
			va_start( ap, lpszFormat );
			nLen = ::_vsntprintf( szTmp, 1024 * i, lpszFormat, ap );
			va_end( ap );
			if ( nLen >= 0 )
			{
				*this = szTmp;				
				delete [] szTmp;
				szTmp = NULL;				
				return nLen;			
			}
			delete [] szTmp;
			szTmp = NULL;
		}
		return -1;
	}
	
	/**
	*  @brief �ַ�������
	*
	*  ����Ϊ�ַ������ݵ�ʵ�ʳ���, ������C����ַ����Ľ�����־
	*
	*  @return �ַ�������
	*/
	int Length( ) const
	{
		//return m_nSize - 1;
		return ::_tcslen( m_lpszStr );
	}
	
	/**
	*  @brief �ж��ַ����Ƿ�Ϊ��
	*
	*  Ϊ����ζ��ʲôҲ������, Ҳ�����ַ����ĳ���Ϊ0
	*
	*  @return ����ַ���Ϊ��,����TRUE,����,����FALSE
	*/
	int IsEmpty( ) const
	{
		return *m_lpszStr == NULL && m_nSize == 1;
	}
	
	/**
	*  @brief ����ַ���
	*
	*  ɾ��ԭ�����ַ�������, ��ʼ������Ϊ0
	*
	*  @return ��
	*/
	void Clear()
	{
		delete [] m_lpszStr;
		m_lpszStr = NULL;
		m_nSize = 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		m_lpszStr[0] = 0;
	}
	
	/**
	*  @brief �����ַ���
	*
	*  ��ָ��λ�ò������ַ���
	*
	*  @param lpszData    �����ҵ����ַ���
	*  @param nStart      ��ʼλ��
	*  @return int        ����ҵ����ַ������򷵻��Ӵ�����ʼλ�ã����򷵻�
	*/
	int FindWord( const TCHAR * lpszData, int nStart = 0 ) const
	{
		int flag = 0;
		int i;
		for ( i = nStart - 1; i < static_cast<int>( m_nSize - ::_tcslen( lpszData ) ); i++ )
		{
			flag = 0;
			for ( int j = 0; j < static_cast<int>( ::_tcslen( lpszData ) ); j++ )
			{
				if ( m_lpszStr[ i + j ] != lpszData[ j ] )
				{
					flag = 1;
					break;
				}
			}
			if( flag == 0 )
			{
				break;
			}
		}
		if( flag == 0 )
		{
			return i + 1;
		}
		
		return -1;
	}
	
	/**
	*  @brief �滻�ַ���
	*
	*  ���ַ�����ָ�����Ӵ��滻���´�
	*
	*  @param lpszOld Ҫ�滻���Ӵ�
	*  @param lpszNew �ỻ�ɵ��´�
	*  @return �滻�Ĵ���
	*/
	int Replace( const TCHAR* lpszOld, const TCHAR* lpszNew )
	{
		TCHAR * szSource = NULL;
		
		szSource = new TCHAR[ TSTRING_MAX_FORMAT_CHARS ];
		if ( NULL == szSource )
			return -3;

		__try
		{
			::_tcscpy( szSource, m_lpszStr );

			TCHAR * p;
			TCHAR * pOld;
			int nLen;
			int offset = ::_tcslen( lpszNew ) - ::_tcslen( lpszOld );
			
			if( ( pOld = ::_tcsstr( szSource, lpszOld ) ) == NULL )
			{
				return -1;
			}
			
			while ( pOld )
			{
				if ( offset > 0 )
				{
					if( static_cast<int>( ::_tcslen( szSource ) ) + offset > TSTRING_MAX_FORMAT_CHARS )
					{
						return -2;
					}
				}
				else if ( offset == 0 )
				{
					::memcpy( pOld, lpszNew, _tcslen( lpszNew ) );
					pOld = ::_tcsstr(pOld + ::_tcslen( lpszNew ), lpszOld );
					continue;
				}
				p = szSource;
				while( *p )
				{
					p++;
				}
				nLen = p - pOld - ::_tcslen(lpszOld);
				if ( offset != 0 )
				{
					if( offset < 0 )
						p -= nLen;
					p += offset;
					
					nLen++;
					while ( nLen )
					{
						*p = *( p - offset );
						if ( offset > 0 )
						{
							p--;
						}
						else
						{
							p++;
						}
						nLen--;
					}
				}
				::memcpy( pOld, lpszNew, ::_tcslen( lpszNew ) );
				pOld = _tcsstr( pOld + ::_tcslen( lpszNew ), lpszOld );
			}
			*this = szSource;
		}
		__finally
		{
			if ( szSource )
				delete [] szSource, szSource = NULL;
		}

		return 0;
	}
	
	/**
	*  @brief ��鵱ǰ�ַ����Ƿ����
	*
	*  ��鵱ǰ�ַ����������Ƿ����
	*
	*  @return BOOL ���ַ������ݲ������򷵻�TRUE,��֮����FALSE
	*/
	BOOL IsDirty( )
	{
		return ( ::_tcslen( m_lpszStr ) != static_cast<unsigned int>( ( m_nSize - 1 ) ) );
	}
	
	/**
	*  @brief ����ǰ�ַ����������ַ�Сд��
	*
	*  @return TString&    Сд������ַ���
	*/
	TString & MakeLower( )
	{
		::_tcslwr( m_lpszStr );
		return *this;
	}
	
	/**
	*  @brief ����ǰ�ַ����������ַ���д��
	*
	*  @return TString&    ��д������ַ���
	*/
	TString & MakeUpper()
	{
		::_tcsupr( m_lpszStr );
		return *this;
	}	
	
	/**
	*  @brief ���ص�ǰ�ַ�����Ӧ��C���͵���0��β���ַ���
	*
	*  @return const TCHAR*
	*/
	const TCHAR* c_str( ) const
	{
		return m_lpszStr;
	}
	
	/**
	*  @brief ��ʼ���ַ�����д������
	*
	*  @param nCount     Ҫд����ַ�����
	*  @return TCHAR*    ��д���ַ����ݵ��ַ�����ָ��
	*/
	TCHAR* BeginBuffer( int nCount )
	{
		delete [] m_lpszStr;
		m_lpszStr = NULL;
		
		m_nSize = nCount + 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		::memset( m_lpszStr, 0, m_nSize * sizeof( TCHAR ) );
		
		return m_lpszStr;
	}
	
	/**
	*  @brief �����ַ�����д�������������ʵ�ʳ��������ַ����ռ估�����Ϣ
	*
	*  @return TString&    ������Ϻ���ַ���
	*/
	TString& EndBuffer( )
	{
		m_nSize = ::_tcslen( m_lpszStr ) + 1;
		
		TCHAR * pTemp = new TCHAR[ m_nSize ];
		::_tcscpy( pTemp, m_lpszStr );
		
		delete [] m_lpszStr;
		m_lpszStr = pTemp;
		
		return *this;
	}
	
	/**
	*  @brief �ַ��������ļ�
	*
	*  ���ַ�������ָ�����ļ���
	*
	*  @param lpszFileName �ļ���
	*  @return BOOL �Ƿ񱣴�ɹ�
	*/
	BOOL SaveToFile( const TCHAR* lpszFileName )
	{
		FILE * stream;
		stream  = ::_tfopen( lpszFileName, _T( "w+b" ) );
		if ( stream == NULL )
		{
			return FALSE;
		}
		
		unsigned int nLen = ::fwrite( m_lpszStr, sizeof( TCHAR ), Length(), stream );
		
		::fclose( stream );
		
		if ( nLen != Length() * sizeof( TCHAR ) )
		{
			return FALSE;
		}
		
		return TRUE;
	}
	
	/**
	*  @brief ��ָ�����ļ��ж����ַ���
	*
	*  ��ָ�����ļ��ж����ַ���
	*
	*  @param lpszFileName �ļ���
	*  @return BOOL �Ƿ��ȡ�ɹ�
	*/
	BOOL LoadFromFile( const TCHAR* lpszFileName )
	{
		FILE * stream;
		stream  = ::_tfopen( lpszFileName, _T( "r+b" ) );		
		if ( stream == NULL )
		{
			return FALSE;
		}
		
		::fseek( stream, 0, SEEK_END );
		int nLen = ftell( stream );
		::fseek( stream, 0, SEEK_SET );
		
		delete [] m_lpszStr;
		m_lpszStr = NULL;
		
		m_nSize = ( nLen / sizeof( TCHAR ) ) + 1;
		m_lpszStr = new TCHAR[ m_nSize ];
		::memset( m_lpszStr, 0, m_nSize * sizeof( TCHAR ) );
		
		nLen = ::fread( m_lpszStr, nLen, 1, stream );
		
		::fclose( stream );
		
		return IsDirty();
	}
};// TString �ඨ�����

#endif
