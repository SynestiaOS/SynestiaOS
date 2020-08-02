//
// Created by XingfengYang on 2020/7/7.
//

#include <kheap.h>
#include <log.h>
#include <mailbox.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

struct mbox_registers {
  const volatile uint32_t read_0; // 0x00         Read data from VC to ARM
  uint32_t unused[3];             // 0x04-0x0F
  volatile uint32_t peek_0;       // 0x10
  volatile uint32_t sender_0;     // 0x14
  volatile uint32_t status_0;     // 0x18         Status of VC to ARM
  volatile uint32_t config0;      // 0x1C
  volatile uint32_t write_1;      // 0x20         Write data from ARM to VC
  uint32_t unused_2[3];           // 0x24-0x2F
  volatile uint32_t peek_1;       // 0x30
  volatile uint32_t sender_1;     // 0x34
  volatile uint32_t status_1;     // 0x38         Status of ARM to VC
  volatile uint32_t config_1;     // 0x3C
} __attribute__((__packed__, aligned(4)));

uint32_t mailbox_call(uint8_t channel, uint32_t mailbox) {
  mailbox_write(channel, mailbox);
  uint32_t data = mailbox_read(channel);
  return data;
}

uint32_t mailbox_read(uint8_t channel) {
  // Loop until we receive something from the requested channel
  for (;;) {
    while ((*(uint32_t *)(MAIL0_STATUS)&MBOX_EMPTY) != 0) {
      // Wait for data
    }
    // Read the data
    uint32_t data = *(uint32_t *)(MAIL0_READ);
    uint32_t readChannel = data & 0xF;
    data >>= 4;
    // Return it straight away if it's for the requested channel
    if (readChannel == channel) {
      return data;
    }
  }
}

void mailbox_write(uint8_t channel, uint32_t data) {
  while ((*(uint32_t *)(MAIL0_STATUS)&MBOX_FULL) != 0) {
    // Wait for data
  }
  // Write the value to the requested channel
  *(uint32_t *)(MAIL0_WRITE) = ((data & ~0xF) | channel);
}

uint32_t mailboxSetPropertyGetFirmwareRevision(PropertyGetFirmwareRevision property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetBoardModel(PropertyGetBoardModel property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetBoardRevision(PropertyGetBoardRevision property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetBoardMacAddress(PropertyGetBoardMacAddress property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetBoardSerial(PropertyGetBoardSerial property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetArmMemory(PropertyGetArmMemory property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetVideoCoreMemory(PropertyGetVideoCoreMemory property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetClocks(PropertyGetClocks property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetCommandLine(PropertyGetCommandLine property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetDMAChannels(PropertyGetDMAChannels property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetPowerState(PropertyGetPowerState property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetTiming(PropertyGetTiming property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetPowerState(PropertySetPowerState property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetClockState(PropertyGetClockState property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetClockState(PropertySetClockState property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetClockRate(PropertyGetClockRate property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetClockRate(PropertySetClockRate property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetMaxClockRate(PropertyGetMaxClockRate property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetMinClockRate(PropertyGetMinClockRate property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetTurbo(PropertyGetTurbo property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetTurbo(PropertySetTurbo property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetVoltage(PropertyGetVoltage property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetVoltage(PropertySetVoltage property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetMaxVoltage(PropertyGetMaxVoltage property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetMinVoltage(PropertyGetMinVoltage property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetTemperature(PropertyGetTemperature property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetMaxTemperature(PropertyGetMaxTemperature property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyAllocateMemory(PropertyAllocateMemory property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyLockMemory(PropertyLockMemory property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyUnLockMemory(PropertyUnLockMemory property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyReleaseMemory(PropertyReleaseMemory property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyExecuteCode(PropertyExecuteCode property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetDispmanxResourceMemHandle(PropertyGetDispmanxResourceMemHandle property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetEDIDBlock(PropertyGetEDIDBlock property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyAllocateBuffer(PropertyAllocateBuffer property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyReleaseBuffer(PropertyReleaseBuffer property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyBlankScreen(PropertyBlankScreen property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetPhysicalDisplayWH(PropertyGetPhysicalDisplayWH property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestPhysicalDisplayWH(PropertyTestPhysicalDisplayWH property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetPhysicalDisplayWH(PropertySetPhysicalDisplayWH property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetVirtualBufferWH(PropertyGetVirtualBufferWH property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestVirtualBufferWH(PropertyTestVirtualBufferWH property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetVirtualBufferWH(PropertySetVirtualBufferWH property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetDepth(PropertyGetDepth property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestDepth(PropertyTestDepth property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetDepth(PropertySetDepth property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetPixelOrder(PropertyGetPixelOrder property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestPixelOrder(PropertyTestPixelOrder property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetPixelOrder(PropertySetPixelOrder property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetAlphaMode(PropertyGetAlphaMode property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestAlphaMode(PropertyTestAlphaMode property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetAlphaMode(PropertySetAlphaMode property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetPitch(PropertyGetPitch property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetVirtualOffset(PropertyGetVirtualOffset property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestVirtualOffset(PropertyTestVirtualOffset property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetVirtualOffset(PropertySetVirtualOffset property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetOverscan(PropertyGetOverscan property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestOverscan(PropertyTestOverscan property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetOverscan(PropertySetOverscan property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyGetPalette(PropertyGetPalette property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertyTestPalette(PropertyTestPalette property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetPalette(PropertySetPalette property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetCursorInfo(PropertySetCursorInfo property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}

uint32_t mailboxSetPropertySetCursorState(PropertySetCursorState property) {
  uint32_t size = sizeof(property) + 3 * sizeof(uint32_t);
  uint32_t *mail = (uint32_t *)kheap_alloc_aligned(size, 16);
  if (mail == nullptr) {
    LogError("[MailBox]: mail alloc failed.\n");
    return 0;
  }
  mail[0] = size;
  mail[1] = MBOX_REQUEST;
  memcpy(&mail[2], &property, sizeof(property));
  mail[(size / 4) - 1] = PROPERTY_TAG_END;

  uint32_t data = mailbox_call(MAILBOX_CHANNEL_PROPERTY_TAGS_ARM_TO_VC, (uint32_t)&mail);

  KernelStatus status = kheap_free(mail);
  if (status == ERROR) {
    LogWarn("[MailBox]: mail free failed.\n");
  }

  return data;
}
