/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Extensible Firmware Interface
 * Based on 'Extensible Firmware Interface Specification' version 0.9,
 * April 30, 1999
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999, 2002-2003 Hewlett-Packard Co.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 *
 * Copyright (C) 2020 Loongson Technology Corporation Limited
 * From include/linux/efi.h in kernel 4.1 with some additions/subtractions
 */

#ifndef _EFI_API_H
#define _EFI_API_H

#include <efi.h> 
#include <stdio.h>

/* UEFI spec version 2.8 */
#define EFI_SPECIFICATION_VERSION (2 << 16 | 80)
#define efi_intn_t sint
#define efi_uintn_t int
#define FW_VERSION 0x1
#define FW_PATCHLEVEL 0x0
/* EFI Boot Services table */
#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
/* EFI Runtime Services table */
#define EFI_RUNTIME_SERVICES_SIGNATURE	0x56524553544e5552ULL
#define EFI_SYSTEM_TABLE_SIGNATURE ((u64)0x5453595320494249ULL)

/* Maximum number of configuration tables */
#define EFI_MAX_CONFIGURATION_TABLES 16

typedef void *efi_hii_handle_t;
typedef u16 *efi_string_t;
typedef u16 efi_string_id_t;
typedef u32 efi_hii_font_style_t;
typedef u16 efi_question_id_t;
typedef u16 efi_image_id_t;
typedef u16 efi_form_id_t;

struct efi_event;


/* Types and defines for EFI CreateEvent */
enum efi_timer_delay {
	EFI_TIMER_STOP = 0,
	EFI_TIMER_PERIODIC = 1,
	EFI_TIMER_RELATIVE = 2
};

struct efi_boot_services {
	struct efi_table_hdr hdr;
	efi_status_t (*raise_tpl)(efi_uintn_t new_tpl);
	void (*restore_tpl)(efi_uintn_t old_tpl);

	efi_status_t (*allocate_pages)(int, int, efi_uintn_t,
			efi_physical_addr_t *);
	efi_status_t (*free_pages)(efi_physical_addr_t, efi_uintn_t);
	efi_status_t (*get_memory_map)(efi_uintn_t *memory_map_size,
			struct efi_mem_desc *desc,
			efi_uintn_t *key,
			efi_uintn_t *desc_size,
			u32 *desc_version);
	efi_status_t (*allocate_pool)(int, efi_uintn_t, void **);
	efi_status_t (*free_pool)(void *);

	efi_status_t (*create_event)(uint32_t type,
			efi_uintn_t notify_tpl,
			void (*notify_function) (
					struct efi_event *event,
					void *context),
			void *notify_context, struct efi_event **event);
	efi_status_t (*set_timer)(struct efi_event *event,
					 enum efi_timer_delay type,
					 uint64_t trigger_time);
	efi_status_t (*wait_for_event)(efi_uintn_t number_of_events,
			struct efi_event **event, efi_uintn_t *index);
	efi_status_t (*signal_event)(struct efi_event *event);
	efi_status_t (*close_event)(struct efi_event *event);
	efi_status_t (*check_event)(struct efi_event *event);
#define EFI_NATIVE_INTERFACE	0x00000000
	efi_status_t (*install_protocol_interface)(
			efi_handle_t *handle, const efi_guid_t *protocol,
			int protocol_interface_type, void *protocol_interface);
	efi_status_t (*reinstall_protocol_interface)(
			efi_handle_t handle, const efi_guid_t *protocol,
			void *old_interface, void *new_interface);
	efi_status_t (*uninstall_protocol_interface)(
			efi_handle_t handle, const efi_guid_t *protocol,
			void *protocol_interface);
	efi_status_t (*handle_protocol)(
			efi_handle_t handle, const efi_guid_t *protocol,
			void **protocol_interface);
	void *reserved;
	efi_status_t (*register_protocol_notify)(
			const efi_guid_t *protocol, struct efi_event *event,
			void **registration);
	efi_status_t (*locate_handle)(
			enum efi_locate_search_type search_type,
			const efi_guid_t *protocol, void *search_key,
			efi_uintn_t *buffer_size, efi_handle_t *buffer);
	efi_status_t (*locate_device_path)(const efi_guid_t *protocol,
			struct efi_device_path **device_path,
			efi_handle_t *device);
	efi_status_t (*install_configuration_table)(
			efi_guid_t *guid, void *table);

	efi_status_t (*load_image)(int boot_policiy,
			efi_handle_t parent_image,
			struct efi_device_path *file_path, void *source_buffer,
			efi_uintn_t source_size, efi_handle_t *image);
	efi_status_t (*start_image)(efi_handle_t handle,
					   efi_uintn_t *exitdata_size,
					   u16 **exitdata);
	efi_status_t (*exit)(efi_handle_t handle,
				    efi_status_t exit_status,
				    efi_uintn_t exitdata_size, u16 *exitdata);
	efi_status_t (*unload_image)(efi_handle_t image_handle);
	efi_status_t (*exit_boot_services)(efi_handle_t image_handle,
						  efi_uintn_t map_key);

	efi_status_t (*get_next_monotonic_count)(u64 *count);
	efi_status_t (*stall)(unsigned long usecs);
	efi_status_t (*set_watchdog_timer)(unsigned long timeout,
			uint64_t watchdog_code, unsigned long data_size,
			uint16_t *watchdog_data);
	efi_status_t(*connect_controller)(efi_handle_t controller_handle,
			efi_handle_t *driver_image_handle,
			struct efi_device_path *remaining_device_path,
			int recursive);
	efi_status_t (*disconnect_controller)(
			efi_handle_t controller_handle,
			efi_handle_t driver_image_handle,
			efi_handle_t child_handle);
	efi_status_t (*open_protocol)(efi_handle_t handle,
			const efi_guid_t *protocol, void **interface,
			efi_handle_t agent_handle,
			efi_handle_t controller_handle, u32 attributes);
	efi_status_t (*close_protocol)(
			efi_handle_t handle, const efi_guid_t *protocol,
			efi_handle_t agent_handle,
			efi_handle_t controller_handle);
	efi_status_t(*open_protocol_information)(efi_handle_t handle,
			const efi_guid_t *protocol,
			struct efi_open_protocol_info_entry **entry_buffer,
			efi_uintn_t *entry_count);
	efi_status_t (*protocols_per_handle)(efi_handle_t handle,
			efi_guid_t ***protocol_buffer,
			efi_uintn_t *protocols_buffer_count);
	efi_status_t (*locate_handle_buffer) (
			enum efi_locate_search_type search_type,
			const efi_guid_t *protocol, void *search_key,
			efi_uintn_t *no_handles, efi_handle_t **buffer);
	efi_status_t (*locate_protocol)(const efi_guid_t *protocol,
			void *registration, void **protocol_interface);
	efi_status_t (*install_multiple_protocol_interfaces)(
			efi_handle_t *handle, ...);
	efi_status_t (*uninstall_multiple_protocol_interfaces)(
			efi_handle_t handle, ...);
	efi_status_t (*calculate_crc32)(const void *data,
			efi_uintn_t data_size,
			u32 *crc32);
	void (*copy_mem)(void *destination, const void *source,
			int length);
	void (*set_mem)(void *buffer, int size, uint8_t value);
	efi_status_t (*create_event_ex)(
				uint32_t type, efi_uintn_t notify_tpl,
				void (*notify_function) (
					struct efi_event *event,
					void *context),
				void *notify_context,
				efi_guid_t *event_group,
				struct efi_event **event);
};

/* Types and defines for EFI ResetSystem */
enum efi_reset_type {
	EFI_RESET_COLD = 0,
	EFI_RESET_WARM = 1,
	EFI_RESET_SHUTDOWN = 2,
	EFI_RESET_PLATFORM_SPECIFIC = 3,
};

struct efi_capsule_header {
	efi_guid_t capsule_guid;
	u32 header_size;
	u32 flags;
	u32 capsule_image_size;
};

struct efi_runtime_services {
	struct efi_table_hdr hdr;
	efi_status_t (*get_time)(struct efi_time *time,
			struct efi_time_cap *capabilities);
	efi_status_t (*set_time)(struct efi_time *time);
	efi_status_t (*get_wakeup_time)(char *enabled, char *pending,
			struct efi_time *time);
	efi_status_t (*set_wakeup_time)(char enabled,
			struct efi_time *time);
	efi_status_t (*set_virtual_address_map)(
			efi_uintn_t memory_map_size,
			efi_uintn_t descriptor_size,
			uint32_t descriptor_version,
			struct efi_mem_desc *virtmap);
	efi_status_t (*convert_pointer)(
			efi_uintn_t debug_disposition, void **address);
	efi_status_t (*get_variable)(u16 *variable_name,
			const efi_guid_t *vendor,
			u32 *attributes,
			efi_uintn_t *data_size, void *data);
	efi_status_t (*get_next_variable_name)(
			efi_uintn_t *variable_name_size,
			u16 *variable_name, efi_guid_t *vendor);
	efi_status_t (*set_variable)(u16 *variable_name,
			const efi_guid_t *vendor,
			u32 attributes, efi_uintn_t data_size,
			const void *data);
	efi_status_t (*get_next_high_mono_count)(
			uint32_t *high_count);
	void (*reset_system)(enum efi_reset_type reset_type,
			efi_status_t reset_status,
			unsigned long data_size, void *reset_data);
	efi_status_t (*update_capsule)(
			struct efi_capsule_header **capsule_header_array,
			efi_uintn_t capsule_count,
			u64 scatter_gather_list);
	efi_status_t (*query_capsule_caps)(
			struct efi_capsule_header **capsule_header_array,
			efi_uintn_t capsule_count,
			u64 *maximum_capsule_size,
			u32 *reset_type);
	efi_status_t (*query_variable_info)(
			u32 attributes,
			u64 *maximum_variable_storage_size,
			u64 *remaining_variable_storage_size,
			u64 *maximum_variable_size);
};

/* EFI Configuration Table and GUID definitions */
#define NULL_GUID \
	EFI_GUID(0x00000000, 0x0000, 0x0000, 0x00, 0x00, \
		 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

#define EFI_FDT_GUID \
	EFI_GUID(0xb1b621d5, 0xf19c, 0x41a5, \
		 0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0)

#define EFI_ACPI_TABLE_GUID \
	EFI_GUID(0x8868e871, 0xe4f1, 0x11d3, \
		 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81)

#define SMBIOS_TABLE_GUID \
	EFI_GUID(0xeb9d2d31, 0x2d88, 0x11d3,  \
		 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d)

struct efi_configuration_table {
	efi_guid_t guid;
	void *table;
};

struct efi_system_table {
	struct efi_table_hdr hdr;
	u16 *fw_vendor;   /* physical addr of wchar_t vendor string */
	u32 fw_revision;
	efi_handle_t con_in_handle;
	struct efi_simple_text_input_protocol *con_in;
	efi_handle_t con_out_handle;
	struct efi_simple_text_output_protocol *con_out;
	efi_handle_t stderr_handle;
	struct efi_simple_text_output_protocol *std_err;
	struct efi_runtime_services *runtime;
	struct efi_boot_services *boottime;
	unsigned long nr_tables;
	struct efi_configuration_table *tables;
};

struct efi_system_table systab;
enum EFI_TABLE_ID {
	fdt_table_id = 0,
	max_efi_tables,
};

struct efi_configuration_table efi_tables[max_efi_tables];

static inline int guidcmp(const void *g1, const void *g2)
{
    return memcmp(g1, g2, sizeof(efi_guid_t));
}

static inline void *guidcpy(void *dst, const void *src)
{
    return memcpy(dst, src, sizeof(efi_guid_t));
}

#endif
