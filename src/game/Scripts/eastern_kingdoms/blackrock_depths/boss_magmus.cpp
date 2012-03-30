/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Magmus
SD%Complete: 80
SDComment: Missing pre-event to open doors
SDCategory: Blackrock Depths
EndScriptData */

#include "pchdef.h"
#include "blackrock_depths.h"

enum
{
    SPELL_FIERYBURST        = 13900,
    SPELL_WARSTOMP          = 24375
};

struct boss_magmusAI : public ScriptedAI
{
    boss_magmusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiFieryBurstTimer;
    uint32 m_uiWarStompTimer;

    void Reset()
    {
        m_uiFieryBurstTimer = 5000;
        m_uiWarStompTimer = 0;
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IRON_HALL, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IRON_HALL, FAIL);
    }

    void JustDied(Unit* pVictim)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IRON_HALL, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //FieryBurst_Timer
        if (m_uiFieryBurstTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FIERYBURST);
            m_uiFieryBurstTimer = 6000;
        }
        else
            m_uiFieryBurstTimer -= uiDiff;

        //WarStomp_Timer
        if (m_creature->GetHealthPercent() < 51.0f)
        {
            if (m_uiWarStompTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_WARSTOMP);
                m_uiWarStompTimer = 8000;
            }
            else
                m_uiWarStompTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_magmus(Creature* pCreature)
{
    return new boss_magmusAI(pCreature);
}

void AddSC_boss_magmus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_magmus";
    pNewScript->GetAI = &GetAI_boss_magmus;
    pNewScript->RegisterSelf();
}
