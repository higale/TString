/**
*  @file TString.h
*  @brief TCHAR字符串类的声明文件
*
*  本文件完成了对TCHAR字符串类 TString 的定义
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

#pragma warning(disable : 4996)	// 不安全字符串操作

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
//#include "stdafx.h"
//#include "stdarg.h"

//! 最大字符串长度
//const int TSTRING_MAX_CHARS = 2048;

//! Format的格式化串最大长度
const int TSTRING_MAX_FORMAT_CHARS = 102400;

/**
*  @brief TCHAR字符串类
*
*  本类完成了TCHAR字符串的常用操作,使用方法和MFC类库的CString类似
*/
class TString
{
protected:	// 保护数据
	TCHAR* m_lpszStr;		//!< C风格字符串,指向本类的实际字符串数据
	int     m_nSize;		//!< 字符串的长度,包括NULL字符
	
public:	// 构造及析构
	
	/**
	*  @brief 默认构造函数
	*
	*  当不带任何参数构造类时,使用本构造函数, 如:\n
	*  TString strTemp;
	*
	*  @return 无
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
	*  @brief 容器构造函数
	*
	*  创建一个能容纳足够字符的空字符串
	*
	*  @param nLen 字符串的最大长度
	*  @return 无
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
	*  @brief 字符参数的构造函数
	*
	*  用字符参数构造类实例
	*
	*  @param chData 字符
	*  @return 无
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
	*  @brief C风格字符串参数的构造函数
	*
	*  用C风格字符串参数构造类实例, 如:\n
	*  TString strTemp( _T( "Temp" );\n
	*  TString strAbc = _T( "abc" );
	*
	*  @param lpszData C风格字符串
	*  @return 无
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
	*  @brief 复制构造函数
	*
	*  使用另一个另实例作为参数生成新的类实例, 如:\n
	*  TString m_lpszStrA = _T( "abc" );\n
	*  TString m_lpszStrB( m_lpszStrA );
	*
	*  @param strData 用于复制的类实例
	*  @return 无
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
	*  @brief 析构函数
	*
	*  标准析构函数
	*
	*  @return 
	*/
	~TString( )
	{
		delete [] m_lpszStr;
		m_lpszStr = NULL;
	}
	
	
public:	//重载操作符	
	
	/**
	*  @brief =号操作符重载 ( TString类实例 )
	*
	*  以本类的另一个实例对本实例赋值, 如:\n
	*  TString m_lpszStrA = _T( "aaa" );\n
	*  TString m_lpszStrB = m_lpszStrA;
	*
	*  @param strData 本类的另一个实例
	*  @return 实例本身
	*/
	TString& operator = ( const TString &strData )
	{
		return *this = strData.m_lpszStr;
	}
	
	/**
	*  @brief =号操作符重载 ( 字符 )
	*
	*  用字符对本类的实例赋值
	*
	*  @param chData 字符
	*  @return 实例本身
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
	*  @brief =号操作符重载 ( C风格字符串 )
	*
	*  用C风格字符串对本类的实例赋值, 如:\n
	*  TString m_lpszStrA = _T( "aaa" );\n
	*
	*  @param lpszData C风格字符串
	*  @return 实例本身
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
	*  @brief ==操作符重载
	*
	*  和C风格字符串比较
	*
	*  @param lpszData C风格字符串
	*  @return 如果和C风格字符串完全相等,返回TRUE,否则,返回FALSE
	*/
	BOOL operator == ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) == 0 && Length() == static_cast<int>( ::_tcslen( lpszData ) );
	}
	
	/**
	*  @brief !=操作符重载
	*
	*  和C风格字符串比较
	*
	*  @param lpszData C风格字符串
	*  @return 如果和C风格字符串不相同,返回TRUE,否则,返回FALSE
	*/
	BOOL operator != ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) != 0 || Length() != static_cast<int>( _tcslen( lpszData ) );
	}
	
	/**
	*  @brief <操作符重载
	*
	*  和C风格字符串比较, 比较是通过平台的编码完成的,如 ASCII码等, 不同的平台, 可能产生不同的结果
	*
	*  @param lpszData C风格字符串
	*  @return 如果本实例小于参数提供的字符串,返回TRUE,否则,返回FALSE
	*/
	BOOL operator < ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) == -1;
	}
	
	/**
	*  @brief <=操作符重载
	*
	*  和C风格字符串比较, 比较是通过平台的编码完成的,如 ASCII码等, 不同的平台, 可能产生不同的结果
	*
	*  @param lpszData C风格字符串
	*  @return 如果本实例小于或等于参数提供的字符串,返回TRUE,否则,返回FALSE
	*/
	BOOL operator <= ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) != 1;
	}
	
	/**
	*  @brief >操作符重载
	*
	*  和C风格字符串比较, 比较是通过平台的编码完成的,如 ASCII码等, 不同的平台, 可能产生不同的结果
	*
	*  @param lpszData C风格字符串
	*  @return 如果本实例大于参数提供的字符串,返回TRUE,否则,返回FALSE
	*/
	BOOL operator > ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) == 1;
	}
	
	/**
	*  @brief >=操作符重载
	*
	*  和C风格字符串比较, 比较是通过平台的编码完成的,如 ASCII码等, 不同的平台, 可能产生不同的结果
	*
	*  @param lpszData C风格字符串
	*  @return 如果本实例大于或等于参数提供的字符串,返回TRUE,否则,返回FALSE
	*/
	BOOL operator >= ( const TCHAR * lpszData ) const
	{
		return ::_tcscmp( m_lpszStr, lpszData ) != -1;
	}
	
	/**
	*  @brief +操作符重载
	*
	*  完成和C风格字符串的相加 ( 连接字符串 )
	*
	*  @param lpszData C风格字符串
	*  @return 相加后的类实例 ( 连接后的字符串 )
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
	*  @brief 友员 + 操作符重载( C风格字符串 + TString )
	*
	*  完成C风格字符串和本类实例的相加
	*
	*  @param lpszLeft C风格字符串
	*  @param strRight 本类的实例
	*  @return 相加后的类实例 ( 连接后的字符串 )
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
	*  @brief +=操作符重载
	*
	*  将另一个字符串连接到本串的尾部 ( 连接字符串 )
	*
	*  @param lpszData C风格字符串
	*  @return 连接后的类实例 ( 连接后的字符串 )
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
	
public:	// 子串操作
	
	/**
	*  @brief 取子字符串
	*
	*  在指定位置提取指定长度的子字符串
	*
	*  @param nIndex 子字符串的开始位置
	*  @param nCount 子字符串的长度
	*  @return 子字符串
	*/
	TString SubStr( int nIndex, int nCount ) const
	{
		TString strTmp;
		int i;
		
		// 判断传入的子字符串的开始位置是否有效 :
		if ( ( nIndex <= 0 ) || ( nIndex >= m_nSize ) )
		{
			return strTmp;
		}
		// 结束 ( 判断传入的子字符串的开始位置是否有效 )
		
		// 判断传入的子字符串的长度是否有效 :
		if ( ( nIndex + nCount ) >= m_nSize )
		{
			nCount = m_nSize - nIndex;
		}
		// 结束 ( 判断传入的子字符串的长度是否有效 )
		
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
	*  @brief 插入子字符串
	*
	*  在指定位置插入一个子字符串
	*
	*  @param lpszData 要插入的子字符串
	*  @param nIndex   插入的位置
	*  @return 无
	*/
	void Insert( const TCHAR * lpszData, int nIndex )
	{
		// 判断传入的插入的位置是否有效 :
		if ( ( nIndex <= 0 ) || ( nIndex > m_nSize ) )
		{
			return;
		}
		// 结束 ( 判断传入的子字符串的开始位置是否有效 )
		
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
	*  @brief 删除子字符串
	*
	*  在指定位置删除指定长度的子字符串
	*
	*  @param nIndex 要删除子串的起始位置
	*  @param nCount 要删除子串的长度
	*  @return 无
	*/
	void Remove( int nIndex, int nCount )
	{
		int i;

		// 判断传入的要删除子串的起始位置是否有效 :
		if ( ( nIndex <= 0 ) || ( nIndex >= m_nSize ) )
		{
			return;
		}
		// 结束 ( 判断传入的要删除子串的起始位置是否有效 )
		
		// 判断传入的要删除子串的长度是否有效 :
		if ( ( nIndex + nCount ) > m_nSize )
		{
			nCount = m_nSize - nIndex;
		}
		// 结束 ( 判断传入的要删除子串的长度是否有效 )
		
		for ( i = nIndex - 1; i < ( m_nSize - nCount - 1 ); i++ )
		{
			m_lpszStr[ i ] = m_lpszStr[ i + nCount ];
		}
		m_lpszStr[ i ] = _T( '\0' );
		
		m_nSize -= nCount;
	}
	
public: // 下标及强制类型转换定义

	/**
	*  @brief 下标运算
	*
	*  完成字符串数组的模拟操作
	*
	*  @param n 数组下标
	*  @return 指定下标的字符引用
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
	*  @brief 强制转换成const TCHAR*型
	*
	*  由于本操作符重载的存在, 可以象使用TCHAR*一样使用本类的实例,\n
	*  为了防止破坏成员数据, 返回的指针使用const进行了限制.\n
	*  对其写入数据时应注意, 由于转换时使用了const, 所以不能直接进\n
	*  行写操作, 如果确认要执行写入, 可以使用如下转换:\n
	*  TString m_lpszStrTmp = _T( "abcd" );\n
	*  const_cast<TCHAR*>( static_cast<const TCHAR*>(m_lpszStrTmp) );\n
	*  同时要注意,写入时不要超出其使用的数据长度.\n
	*  ( 由于写入操作是直接针对类的成员数据区, 这违反了类的封装原则,应尽量避免这种情况的出现 )
	*
	*  @return operator _const TCHAR*
	*/
	operator const TCHAR* ( ) const
	{
		return m_lpszStr;
	}
	
public:	//其他函数
	
	/**
	*  @brief 格式化字符串
	*
	*  使用方法类似于 sprintf 函数
	*
	*  @param lpszFormat 格式化字符串
	*  @param ... 要格式的变量列表
	*  @return int 格式化后的字符串长度
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
	*  @brief 字符串长度
	*
	*  长度为字符串内容的实际长度, 不包括C风格字符串的结束标志
	*
	*  @return 字符串长度
	*/
	int Length( ) const
	{
		//return m_nSize - 1;
		return ::_tcslen( m_lpszStr );
	}
	
	/**
	*  @brief 判断字符串是否为空
	*
	*  为空意味着什么也不包括, 也就是字符串的长度为0
	*
	*  @return 如果字符串为空,返回TRUE,否则,返回FALSE
	*/
	int IsEmpty( ) const
	{
		return *m_lpszStr == NULL && m_nSize == 1;
	}
	
	/**
	*  @brief 清空字符串
	*
	*  删除原来的字符串内容, 初始化长度为0
	*
	*  @return 无
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
	*  @brief 查找字符串
	*
	*  从指定位置查找子字符串
	*
	*  @param lpszData    待查找的子字符串
	*  @param nStart      开始位置
	*  @return int        如果找到子字符串，则返回子串的起始位置，否则返回
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
	*  @brief 替换字符串
	*
	*  把字符串中指定的子串替换成新串
	*
	*  @param lpszOld 要替换的子串
	*  @param lpszNew 提换成的新串
	*  @return 替换的次数
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
	*  @brief 检查当前字符串是否可用
	*
	*  检查当前字符串的数据是否可用
	*
	*  @return BOOL 若字符串数据不可用则返回TRUE,反之返回FALSE
	*/
	BOOL IsDirty( )
	{
		return ( ::_tcslen( m_lpszStr ) != static_cast<unsigned int>( ( m_nSize - 1 ) ) );
	}
	
	/**
	*  @brief 将当前字符串的所有字符小写化
	*
	*  @return TString&    小写化后的字符串
	*/
	TString & MakeLower( )
	{
		::_tcslwr( m_lpszStr );
		return *this;
	}
	
	/**
	*  @brief 将当前字符串的所有字符大写化
	*
	*  @return TString&    大写化后的字符串
	*/
	TString & MakeUpper()
	{
		::_tcsupr( m_lpszStr );
		return *this;
	}	
	
	/**
	*  @brief 返回当前字符串对应的C类型的以0结尾的字符串
	*
	*  @return const TCHAR*
	*/
	const TCHAR* c_str( ) const
	{
		return m_lpszStr;
	}
	
	/**
	*  @brief 开始向字符串里写入数据
	*
	*  @param nCount     要写入的字符个数
	*  @return TCHAR*    待写入字符数据的字符数组指针
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
	*  @brief 结束字符串的写入操作，并按照实际长度整理字符串空间及相关信息
	*
	*  @return TString&    整理完毕后的字符串
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
	*  @brief 字符串存入文件
	*
	*  将字符串存入指定的文件中
	*
	*  @param lpszFileName 文件名
	*  @return BOOL 是否保存成功
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
	*  @brief 从指定的文件中读入字符串
	*
	*  从指定的文件中读入字符串
	*
	*  @param lpszFileName 文件名
	*  @return BOOL 是否读取成功
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
};// TString 类定义结束

#endif
