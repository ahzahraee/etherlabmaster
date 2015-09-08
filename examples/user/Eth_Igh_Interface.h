
/*
 +-------------------------------------------------------------------------+
 |                                                                         |
 |     Projet  :   Ethercat                                                |
 |                                                                         |
 |     Module  :   Eth_Igh_Interface.h                                       |
 |     Version :   1.0                                                   |
 |                                                                         |
 |     Auteur  :   Ali HASSAN ZAHRAEE                                             |
 |     Date    :   07/07/2015                                              |
 |                                                                         |
 +-------------------------------------------------------------------------+
 |                                                                         |
 |     Description  :  Interface Ethercat en utilisant la pile Igh         |
 |     																	   |
 +-------------------------------------------------------------------------+
 */


#ifndef __Eth_Igh_Interface__
#define __Eth_Igh_Interface__

#include "ecrt.h"

#define MAX_DOMAINS	4
uint8_t* domains_pd[MAX_DOMAINS];


typedef		unsigned short		EC_T_WORD;
typedef		unsigned int		EC_T_DWORD;
typedef		char				EC_T_CHAR;
typedef		int					EC_T_BOOL;
typedef		unsigned char		EC_T_BYTE;
typedef		unsigned int		UINT;

#define		EC_T_VOID			void
#define		EC_FALSE			0
#define		EC_TRUE				1
#define		EC_NULL				0

#define		EC_E_NOERROR		((EC_T_DWORD)0x00000000)
#define     EC_E_ERROR			((EC_T_DWORD)0x98110000)




/* ---------------------------------------------------------------------- */
/* ------------------------------- PROTOCOLES --------------------------- */
/* ---------------------------------------------------------------------- */
 /* Protocoles de communication actuellement supportes
	COE (Canopen Over Ethercat)
	SERCOS */
#define		PROTOCOLE_COE								0
#define		PROTOCOLE_SERCOS							1


/* ---------------------------------------------------------------------- */
/* ------------------------------- VARIATEURS --------------------------- */
/* ---------------------------------------------------------------------- */
/* Commandes protocole CoE */
#define		DISABLE_VOLTAGE							0x00	/*							->	switch on disable		*/
#define		SHUTDOWN								0x06	/* switch on disable		->	ready to switch			*/
#define		SWITCH_ON								0X07	/* ready to switch			->	switched on				*/
#define		ENABLE_OPERATION						0x0F	/* switched on				->	enable operation		*/
#define		QUICKSTOP								0x02	/* switched on				->	switch on disable		*/
#define		RESET_FAULT								0x80	/*							->	switch on disable		*/

/* Status */
#define		NO_READY_TO_SWITCH_ON					0x00
#define		SWITCH_ON_DISABLE						0x00
#define		READY_TO_SWITCH_ON						0x01
#define		SWITCHED_ON								0x03
#define		OPERATION_ENABLE						0x07
#define		FAULT									0x08

/* Ordres d'inhibition */
#define		INHIBE									0
#define		DESINHIBE								1

/* Modes de fonctionnement */
	/* Asservissement en position	*/
#define		MODE_CSP								8
	/* Asservissement en vitesse	*/
#define		MODE_CSV								9
	/* Asservissement en couple		*/
#define		MODE_CST								10

/* Retours de la fonction Eth_Power
	DRIVE_READY			: variateur desinhibe
	DRIVE_NOREADY		: variateur inhibe ou en cours de desinhibition
	DRIVE_FAULT			: variateur en erreur */
#define		DRIVE_READY								0
#define		DRIVE_NOREADY							1
#define		DRIVE_FAULT								0X0F



/* ---------------------------------------------------------------------- */
/* ------------------------------- MAXON -------------------------------- */
/* ---------------------------------------------------------------------- */
/* NOTE sur l'EPOS3 : pour passer en mode de fonctionnement normal,
	il est necessaire de transmettre en sequence les commandes suivantes a l'Epos3 :
	SHUTDOWN puis SWITCHON
*/

#define		MAXON_VendorId						0x000000FB

#define		EPOS3_70_10_ProductCode				0x64400000

#define		EPOS3_Index_controlword				0x6040
#define		EPOS3_Subindex_controlword			0

/* Mode de fonctionnement du variateur */
#define		EPOS3_MODE_CSP						MODE_CSP
#define		EPOS3_MODE_CSV						MODE_CSV
#define		EPOS3_MODE_CST						MODE_CST
#define		EPOS3_MODE_PPM						1
#define		EPOS3_MODE_PVM						3

#define		MAXON_VendorName	 "Maxon"
#define		MAXON_ProductCodeName(id,pret) {																					\
											switch(id)																			\
											{																					\
												case EPOS3_70_10_ProductCode		: pret = (EC_T_CHAR*)("EPOS3_70_10");break;	\
												default								: pret = (EC_T_CHAR*)("Inconnu");			\
											};																					\
										  }


/* ---------------------------------------------------------------------- */
/* ------------------------------- AMC ---------------------------------- */
/* ---------------------------------------------------------------------- */

#define		AMC_VendorId						0x000000BD

#define		AMC_DP_DZ_serie_1_axe_ProductCode	0x012D0000

#define		AMC_VendorName	 "Advanced Motion Controls"
#define		AMC_ProductCodeName(id,pret) {																								\
											switch(id)																					\
											{																							\
												case AMC_DP_DZ_serie_1_axe_ProductCode	: pret = (EC_T_CHAR*)("DZEANTU, 1 Axe");break;	\
												default									: pret = (EC_T_CHAR*)("Inconnu");				\
											};																							\
										  }


/* ---------------------------------------------------------------------- */
/* ---------------------------- KOLLMORGEN  ----------------------------- */
/* ---------------------------------------------------------------------- */

#define		AKD_VendorId								0x0000006A
#define		AKD_Pxxx_06_NBCC_E000_ProductCode			0x00414B44

/* Mode PV
	TXPDO : 0X1B20
	RXPDO : 0X1702  */

#define		AKD_VendorName	 "Kollmorgen"
#define		AKD_ProductCodeName(id,pret) {																								\
											switch(id)																					\
											{																							\
												case AKD_Pxxx_06_NBCC_E000_ProductCode	: pret = (EC_T_CHAR*)("AKD Pxxx06 NBCC");break;	\
												default									: pret = (EC_T_CHAR*)("Inconnu");				\
											};																							\
										  }


/* ---------------------------------------------------------------------- */
/* ----------------------------- BECKHOFF --------------------------------*/
/* ---------------------------------------------------------------------- */

#define		BECKHOFF_VendorId					0x00000002


#define		BECKHOFF_AX5106_ProductCode			0x13F26012	/* Variateur 1 axe															*/

#define		BECKHOFF_AX5203_ProductCode			0x14536012	/* Variateur																*/

#define		BECKHOFF_AX5805_ProductCode			0x16AD6012	/* Carte Twinsafe pour variateur Beckhoff									*/

#define		BECKHOFF_EK1100_ProductCode			0x044C2c52  /* Coupleur	Simple															*/
#define		BECKHOFF_EK1818_ProductCode			0x071A2C52  /* Coupleur	avec 8 entrees TOR 24VDC  et  4 sorties TOR	24VDC				*/
#define		BECKHOFF_EK1828_ProductCode			0x07242C52  /* Coupleur	avec 4 entrees TOR 24VDC  et  8 sorties TOR	24VDC				*/

#define		BECKHOFF_EL5032_ProductCode			0x13A83052	/* Entrees Codeur EnDat2.2, 2 voies											*/

#define		BECKHOFF_EL6900_ProductCode			0x1AF43052  /* Twinsafe :  Controleur													*/
#define		BECKHOFF_EL1904_ProductCode			0x07703052	/* Twinsafe :  Entrees TOR (4) 24Vdc										*/
#define		BECKHOFF_EL2904_ProductCode			0x0B583052	/* Twinsafe :  Sorties TOR (4) 24Vdc										*/

#define		BECKHOFF_EL6001_ProductCode			0x17713052  /* 1 channel RS232															*/
#define		BECKHOFF_EL5002_ProductCode			0x138A3052  /* 2 canaux SSI																*/


/* EL5032 : 2 voies EnDat 2.2 en mode compact (position sur 4 octets)
	Status
	------
	bit 0	  : Status_warning
		1	  : Status_error
		2	  : Status_ready ( '1' : pret a etre utilise )
		12	  : Status_diag
		13	  : Status_TxPDO_state
		14,15 : Status_input_cycle_counter
*/


/*  EL5002, 2 canaux SSI Sensor Interface
  TxPDO
  Mot 0 =>
	bit
	15  :  TxPDO toggle
	14  :  TxPDO state
	13  :  Erreur de synchro
	2   :  power failure
	1   :  frame error
	0   :  data error
  Mot 1 => 32 bits de comptage  */
#define		Rx_Tx_PDO_BECKHOFF_EL5002			0										,	4,	16, 32,	16, 32		/* channel1 : status, valeur, channel2 : status, valeur */


/* Liaisons TwinSafe */
/* ----------------- */
/*
	EL6900 : Controleur TwinSafe =>	Acces en ecriture : 32 bits max. Le bit '0' est reserve au traitement de 'ERR_ACK de l'EL6900.
									Acces en lecture  : 32 bits max */
#define		Rx_Tx_PDO_BECKHOFF_EL6900			1,	32									,	1,	32

/* EL1904 : Entrees TOR => Quatres entrees tor. Possibilite de lire l'etat des entrees TOR.
   Octets 0    : non significatif
		  1    : bits 3..0, les quatres bits de pf contiennent l'image des quatres entrees TOR
		  2..5 : non significatifs */
#define		Rx_Tx_PDO_BECKHOFF_EL1904			0										,	6,	8, 8, 8, 8, 8, 8

/* El2904 : Sorties TOR => aucune donnee exploitable accessible par les PDO */
#define		Rx_Tx_PDO_BECKHOFF_EL2904			0										,	0



#define		BECKHOFF_VendorName	"Beckhoff"
#define		BECKHOFF_ProductCodeName(id,pret) {																					\
												switch(id)																		\
												{																				\
													case BECKHOFF_EL1904_ProductCode	: pret = (EC_T_CHAR*)("EL1904");break;	\
													case BECKHOFF_EL2904_ProductCode	: pret = (EC_T_CHAR*)("EL2904");break;	\
													case BECKHOFF_EK1100_ProductCode	: pret = (EC_T_CHAR*)("EK1100");break;	\
													case BECKHOFF_EL6900_ProductCode	: pret = (EC_T_CHAR*)("EL6900");break;	\
													case BECKHOFF_AX5106_ProductCode	: pret = (EC_T_CHAR*)("AX5106");break;	\
													case BECKHOFF_EK1818_ProductCode	: pret = (EC_T_CHAR*)("EK1818");break;	\
													case BECKHOFF_EK1828_ProductCode	: pret = (EC_T_CHAR*)("EK1828");break;	\
													case BECKHOFF_EL5032_ProductCode	: pret = (EC_T_CHAR*)("EL5032");break;	\
													case BECKHOFF_AX5203_ProductCode	: pret = (EC_T_CHAR*)("AX5203");break;	\
													case BECKHOFF_EL6001_ProductCode	: pret = (EC_T_CHAR*)("EL6001");break;	\
													case BECKHOFF_EL5002_ProductCode	: pret = (EC_T_CHAR*)("EL5002");break;	\
													default								: pret = (EC_T_CHAR*)("Inconnu");		\
												};																				\
											  }


/* ---------------------------------------------------------------------- */
/* ------------------------- Macros d'affichage ------------------------- */
/* ---------------------------------------------------------------------- */

#define		VendorName(vid,pret) {																					\
									switch(vid)																		\
									{																				\
										case MAXON_VendorId			: pret = (EC_T_CHAR*)MAXON_VendorName;	 break;	\
										case BECKHOFF_VendorId		: pret = (EC_T_CHAR*)BECKHOFF_VendorName;break;	\
										case AMC_VendorId			: pret = (EC_T_CHAR*)AMC_VendorName		;break;	\
										case AKD_VendorId			: pret = (EC_T_CHAR*)AKD_VendorName		;break;	\
										default						: pret = (EC_T_CHAR*)("Inconnu");				\
									};																				\
								}

#define		ProductCodeName(vid,pid,pret) {																						\
												switch(vid)																		\
												{																				\
													case MAXON_VendorId			: MAXON_ProductCodeName(pid,pret);	  break;	\
													case BECKHOFF_VendorId		: BECKHOFF_ProductCodeName(pid,pret); break;	\
													case AMC_VendorId			: AMC_ProductCodeName(pid,pret);	  break;	\
													case AKD_VendorId			: AKD_ProductCodeName(pid,pret);	  break;	\
													default						: pret = (EC_T_CHAR*)("Inconnu");				\
												};																				\
										 }



/* -------------------------------------------- Horloge distribuee --------------------------------------------------------*/

/* Avec ou sans horloges distribuees*/
#define		DCM_OFF							0
#define		DCM_ON							1

/* -------------------------------------------- Application --------------------------------------------------------*/

static void signal_handler(int signum);

unsigned int Eth_Print_Time();

/* ------------------------------------------------------------------------------------------------------------ */
/* Initialisation du bus Ethercat																				*/
/* ------------------------------------------------------------------------------------------------------------ */

int Eth_Initialise_Ethercat(		EC_T_DWORD	Master_Index,			/* [in]  Index du maitre � initialiser; 0 si un seul master							*/
									EC_T_DWORD	Avec_DCM	);	/* [in]  avec ou sans DCM															*/


/* ------------------------------------------------------------------------------------------------------------ */
/* Initialisation de l'environnement																			*/
/* ------------------------------------------------------------------------------------------------------------ */
/* Doit etre appelee une fois avant la fonction d'initialisation du maitre et l'enregistrement des esclaves
   priorite : priorite des taches serveurs des SDO asynchrones. Ne pas mettre trop basse, les taches serveurs ne sont pas prioritaires. */
/*EC_T_DWORD Eth_Initialise_Environnement( int Priorite_Tache_SDO );*/
int Eth_Initialise_Environnement(	unsigned int Master_Index,		/* [in]  Pointer to Ethercat master		*/
									unsigned int priority,				/* [in]	 Process priority				*/
									unsigned int period_s,				/* [in] Cyclic task period in seconds	*/
									unsigned int period_us,				/* [in] Cyclic task period in microseconds	*/
									EC_T_DWORD	Num_Domains,			/* [in]  Number of domains 				*/
									const ec_pdo_entry_reg_t domain_0_regs[],
									const ec_pdo_entry_reg_t domain_1_regs[],
									const ec_pdo_entry_reg_t domain_2_regs[],
									const ec_pdo_entry_reg_t domain_3_regs[] );



/* ------------------------------------------------------------------------------------------------------------ */
/* Definition d'un esclave dans la table des esclaves															*/
/* ------------------------------------------------------------------------------------------------------------ */
/* Retourne :
			EC_T_DWORD *Handler_Esclave : le handler associe a l'esclave
			EC_T_DWORD :
				EC_E_NOERROR		:	enregistrement effectue
				EC_E_INVALIDINDEX	:	nombre max des esclaves depasse
				EC_E_ERROR			:	esclave deja enregistre

	le parametre : "EC_T_DWORD Protocole" definit le protocole de communication =>
		PROTOCOLE_COE : CoE CanOpen Over Ethercat ( valeur '0', compatible avec les versions precedentes )
		PROTOCOLE_SOE : SoE Sercos Over Ethercat
	Nbre_RxPDO : nombre des RxPDO de l'esclave, suivi de la longueur de chaque champs Rx, puis nombre des TxPDO de l'esclave suivi de la longueur de chaque champs
	exemple :
	dwRes = Eth_Enregistre_un_Esclave(	MAXON_VendorId,														Code du Vendeur
										EPOS3_70_10_ProductCode,											Code de production
										0,																	Instance de l'esclave
										PROTOCOLE_COE,														Protocole de communication, dependant de l'esclave
										&Handler_Esclave_Epos3_0,											Handler de l'esclave
										5,	16, 16, 16,  8, 16,		6,	16, 32, 32, 16, 8, 16	);			5 RxPDO de longueur respective 	16, 16, 16, 8 et 16 bits
																											6 TxPDO de longueur respective 	16, 32, 32, 16, 8 et 16 bits
	NOTE : on se base toujours par rapport a l'esclave :
		RxPDO sont les PDO recus par l'esclave ( maitre -> esclave )
		TxPDO sont les PDO envoyes par l'esclave ( esclave ->maitre )
*/

ec_slave_config_t* Eth_Enregistre_un_Esclave( 		 ec_sync_info_t syncs[],
											 uint16_t alias, uint16_t position,
											 uint32_t vendor_id, uint32_t product_code );

ec_sdo_request_t* Eth_Create_SDO_Channel(	ec_slave_config_t *sc,
								uint16_t index,
								uint8_t subindex,
								size_t size,
								uint32_t timeout);

int Eth_Start_Ethercat (		EC_T_DWORD	Num_Domains		);			/* [in]  Number of domains 				*/

int Eth_Add_Cyclic_Func (		void (*Fonction_Cyclique)()	);		/* [in]  Pointer to cyclic function 	*/


/* ------------------------------------------------------------------------------------------------------------ */
/* Lecture des donnees cycliques d'un esclave (PDO)																*/
/* ------------------------------------------------------------------------------------------------------------ */

/* Indice_Esclave : 0..n  numero de l'esclave dans le reseau
	retourne :
		EC_E_NOERROR		:	absence d'erreur
		EC_E_INVALIDINDEX	:	handler de l'esclave invalide
*/
void Eth_Read_PDO( unsigned int Domain_Index );

void Eth_Write_PDO( unsigned int Domain_Index );


/* Synchronous method, used in real-time context.
 */
uint8_t* Eth_Read_SDO(ec_sdo_request_t *sdo_server);


/* Blocking method. Not to be used in real-time context.
 *
 */
int Eth_Read_SDO_Master(	uint16_t 	slave_position,
							uint16_t 	index,
							uint8_t 	subindex,
							uint8_t * 	target,
							size_t 	target_size,
							size_t * 	result_size,
							uint32_t * 	abort_code );

/* Synchronous method, used in real-time context.
 */
int Eth_Write_SDO(		ec_sdo_request_t *sdo_server,
						uint8_t *data);

void check_domain_state(unsigned int domain_index);

void check_master_state(void);

void check_slave_config_state(char *slavename, ec_slave_config_t *slaveconfig, ec_slave_config_state_t *slaveconfig_state);


#endif
